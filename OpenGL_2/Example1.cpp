// Model-View matrix and Projection matrix
// Orthogonal or Orthographic projection
// Windows Events - Keyboard & Mouse
// Rotate Rectangle

#include "header/Angel.h"
#include "Common/CQuad.h"
#include "Common/CQuadEX1.h"
#include "./Enemy1.h"
#include "./Bullet.h"
#include "./VBullet.h"
#include "./Enemy2.h"
#include "./BG.h"
#include "./Testenemy1.h"

#define SPACE_KEY 32
#define SCREEN_SIZE 600
#define HALF_SIZE (SCREEN_SIZE/2)

// 必須在 glewInit(); 執行完後,在執行物件實體的取得
CQuad *g_pQuad;	// 宣告 Quad 指標物件，結束時記得釋放
BG *g_pBG[3];

Enemy1 *g_pEnemy1[3];
Enemy2 *g_pEnemy2[2];
VBullet *g_pVBullet;
Bullet1 *g_pBullet;
VBullet *VHead, *VGet, *VTail, *VHeadShoot, *VGetShoot, *VTailShoot, *VLink;
float Bx = 10.0f;//角色子彈位置
float By = 10.0f;
float EBx = 10.0f;//敵人子彈位置
float Eby = 10.0f;
float Dir = 1.0f; //敵人2移動方向
int VBulletNum = 0;//敵人子彈數量
int BulletCount = 0;//角色子彈數量
Bullet1 *Head, *Get, *Tail, *HeadShoot, *GetShoot, *TailShoot, *Link;
bool FlagE1 = true;//敵人1是否出現
bool VBFlag = true;//敵人子彈
bool HideB = true;//子彈是否顯示
					// For Model View and Projection Matrix
mat4 g_mxModelView(1.0f);
mat4 g_mxProjection;
mat4 mxInitE2=Translate(-3.0f,3.0f,0.0f);

mat4 mxT = Translate(-1.0f, 2.0f, 0.0f);

// For Rotation
int     g_iAxis = 2; // 旋轉軸，0:X, 1:Y, 2:Z
GLfloat g_fAngle = 0;   // X/Y/Z 三軸的旋轉角度

GLfloat BGTime = 0; //背景時間
GLfloat g_fZAngle = 0;     // 旋轉方向
GLfloat g_fTx = 0, g_fTy = 0;
GLfloat Pos[2] = { 0.0f,0.0f };
float g_Enemy1Time = 0.0f; //敵人1時間
float g_Enemy2Time = 0.0f; //敵人2出現判斷
float g_Enemy2BTime = 0.0f; //敵人2位移時間
float Enemy2Init = -3.0f; //敵人2初始x座標
float i = 0;
//----------------------------------------------------------------------------
// 函式的原型宣告
void IdleProcess();
void Create();
void Shoot();
void VShoot(float, float);
void VRShoot();
void Enemy1AutoRotateion(float);
void Enemy2Action(mat4);
void RShoot();
void BgAction(float);

void init(void)
{
	// 必須在 glewInit(); 執行完後,在執行物件實體的取得
	g_pQuad = new CQuad;
	//  產生 projection 矩陣，此處為產生正投影矩陣
	g_mxProjection = Ortho(-4.0f, 4.0f, -4.0f, 4.0f, -2.0f, 1.0f);
	g_pQuad->SetShader(g_mxModelView, g_mxProjection);

	glClearColor(1.0, 0.58, 0.72, 1.0); // black background
	Create();
}

void Create(void) {
	g_pBG[0] = new BG;
	g_pBG[0]->SetShader(g_mxModelView, g_mxProjection);
	g_pBG[0]->SetTRSMatrix(Translate(10.0f, 10.0f, 0.0f));
	g_pBG[1] = new BG;
	g_pBG[1]->SetShader(g_mxModelView, g_mxProjection);
	g_pBG[1]->SetTRSMatrix(Translate(10.0f, 10.0f, 0.0f));
	g_pBG[2] = new BG;
	g_pBG[2]->SetShader(g_mxModelView, g_mxProjection);
	g_pBG[2]->SetTRSMatrix(Translate(10.0f, 10.0f, 0.0f));
	

	g_pEnemy1[0] = new Enemy1;
	g_pEnemy1[0]->SetShader(g_mxModelView, g_mxProjection);
	g_pEnemy1[0]->SetTRSMatrix(Translate(10.0f, 10.0f, 0.0f));
	g_pEnemy1[1] = new Enemy1;
	g_pEnemy1[1]->SetShader(g_mxModelView, g_mxProjection);
	g_pEnemy1[1]->SetTRSMatrix(Translate(10.0f, 10.0f, 0.0f));
	g_pEnemy1[2] = new Enemy1;
	g_pEnemy1[2]->SetShader(g_mxModelView, g_mxProjection);
	g_pEnemy1[2]->SetTRSMatrix(Translate(10.0f, 10.0f, 0.0f));
	

	g_pEnemy2[0] = new Enemy2;
	g_pEnemy2[0]->SetShader(g_mxModelView, g_mxProjection);
	g_pEnemy2[0]->SetTRSMatrix(Translate(10.0f, 10.0f, 0.0f));
	g_pEnemy2[1] = new Enemy2;
	g_pEnemy2[1]->SetShader(g_mxModelView, g_mxProjection);
	g_pEnemy2[1]->SetTRSMatrix(Translate(10.0f, 10.0f, 0.0f));
	


	VHeadShoot = VTailShoot = NULL;
	g_pVBullet = new VBullet;
	g_pVBullet->SetShader(g_mxModelView, g_mxProjection);

	VHead = VTail = NULL;
	VHead = new VBullet;
	VHead->SetShader(g_mxModelView, g_mxProjection);

	VTail = VHead;

	for (int i = 0;i < 20;i++) {
		VGet = new VBullet;
		VGet->SetShader(g_mxModelView, g_mxProjection);

		VGet->next = NULL;
		VTail->next = VGet;
		VTail = VGet;
	}

	HeadShoot = TailShoot = NULL;
	g_pBullet = new Bullet1;
	g_pBullet->SetShader(g_mxModelView, g_mxProjection);

	Head = Tail = NULL;
	Head = new Bullet1;
	Head->SetShader(g_mxModelView, g_mxProjection);

	Tail = Head;

	for (int i = 0;i < 10;i++) {
		Get = new Bullet1;
		Get->SetShader(g_mxModelView, g_mxProjection);

		Get->next = NULL;
		Tail->next = Get;
		Tail = Get;
	}

}

void BgAction(float dt) {
	mat4 mxBg1;
	BGTime += dt;
	mat4 mxBg = (
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		);
	g_pBG[0]->y = 6.0f;
	g_pBG[1]->y = 4.0f;
	g_pBG[2]->y = 2.0f;

	if (g_pBG[0]->y < -4.0f || g_pBG[1]->y <-4.0f || g_pBG[2]->y<-4.0f) {
		g_pBG[0]->SetTRSMatrix(Translate(0.0f, 8.0f, 0.0f)*Scale(2.0f, 2.0f, 0.0f));
		g_pBG[1]->SetTRSMatrix(Translate(-2.0f, 6.0f, 0.0f)*Scale(2.0f, 2.0f, 0.0f));
		g_pBG[2]->SetTRSMatrix(Translate(2.0f, 4.0f, 0.0f)*Scale(2.0f, 2.0f, 0.0f));
		g_pBG[0]->y = 8.0f;
		g_pBG[1]->y = 6.0f;
		g_pBG[2]->y = 4.0f;
	}
	else {
		if (BGTime >= 3.0f)BGTime -= 3.0f;
		mxBg[1][3] -= 1 * 4.0f * BGTime;
		g_pBG[0]->SetTRSMatrix(Translate(0.0f, 8.0f, 0.0f)*mxBg*Scale(2.0f, 2.0f, 0.0f));
		g_pBG[1]->SetTRSMatrix(Translate(-2.0f, 6.0f, 0.0f)*mxBg*Scale(2.0f, 2.0f, 0.0f));
		g_pBG[2]->SetTRSMatrix(Translate(2.0f, 4.0f, 0.0f)*mxBg*Scale(2.0f, 2.0f, 0.0f));
		g_pBG[0]->y = mxBg[1][3] + 8.0f;
		g_pBG[1]->y = mxBg[1][3] + 6.0f;
		g_pBG[2]->y = mxBg[1][3] + 4.0f;
	}
}
void Enemy1AutoRotateion(float dt) {
	mat4 mxRot, mxT, mxTT, mxTTT;
	mat4 mxS = (
		1, 0, 0, 0,
		0, 1, 0, 1,
		0, 0, 1, 0,
		0, 0, 0, 1
		);

	g_Enemy1Time += dt;
	if (g_Enemy1Time > 3.0f) {
		mxT = Translate(2.0f, 0.5f, 0.0f);
		mxTT = Translate(0.0f, 1.5f, 0.0f);
		mxTTT = Translate(-2.0f, 2.5f, 0.0f);
		g_fZAngle = 2.0f * g_Enemy1Time  * 90.0f;
		mxRot = RotateZ(g_fZAngle);
		g_pEnemy1[0]->SetTRSMatrix(mxT*mxRot);
		g_pEnemy1[1]->SetTRSMatrix(mxTT*mxRot);
		g_pEnemy1[2]->SetTRSMatrix(mxTTT*mxRot);

		if ((Pos[0] < mxT[0][3] + 1.8f && Pos[0] > mxT[0][3] - 1.8f) && (Pos[1] < mxT[1][3] + 1.8f && Pos[1] > mxT[1][3] - 1.8f)) {
			g_pEnemy1[0]->SetTRSMatrix(mxT*mxRot*Scale(2.0f, 2.0f, 0.0f));
		}
		else if ((Pos[0] < mxTT[0][3] + 1.8f && Pos[0] > mxTT[0][3] - 1.8f) && (Pos[1] < mxTT[1][3] + 1.8f && Pos[1] > mxTT[1][3] - 1.8f)) {
			g_pEnemy1[1]->SetTRSMatrix(mxTT*mxRot*Scale(2.0f, 2.0f, 0.0f));
		}
		else if ((Pos[0] < mxTTT[0][3] + 1.8f && Pos[0] > mxTTT[0][3] - 1.8f) && (Pos[1] < mxTTT[1][3] + 1.8f && Pos[1] > mxTTT[1][3] - 1.8f)) {
			g_pEnemy1[2]->SetTRSMatrix(mxTTT*mxRot*Scale(2.0f, 2.0f, 0.0f));
		}
	}
	else;
	if ((g_pEnemy1[0]->Flag==true) && (Bx < mxT[0][3] + 0.3f && Bx > mxT[0][3] - 0.3f) && (By < mxT[1][3] + 0.3f && By > mxT[1][3] - 0.3f)) {
		g_pEnemy1[0]->Flag = false;
		HideB = false;	
	}
	else if ((g_pEnemy1[1]->Flag == true) && (Bx < mxTT[0][3] + 0.3f && Bx > mxTT[0][3] - 0.3f) && (By < mxTT[1][3] + 0.3f && By > mxTT[1][3] - 0.3f)) {
		g_pEnemy1[1]->Flag = false;
		HideB = false;	
	}
	else if ((g_pEnemy1[2]->Flag == true) && (Bx < mxTTT[0][3] + 0.3f && Bx > mxTTT[0][3] - 0.3f) && (By < mxTTT[1][3] + 0.3f && By > mxTTT[1][3] - 0.3f)) {
		g_pEnemy1[2]->Flag = false;
		HideB = false;	
	}
}

void Enemy2Action(float dt) {
	
	mat4 mxE2 = (
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		);
	
	/*Print(g_pEnemy2[0]->x);*/
	
	g_Enemy2BTime += dt;
	mxE2[0][3] += (Dir)* g_Enemy2BTime;
	g_pEnemy2[0]->SetTRSMatrix(mxInitE2*mxE2*Scale(2.0f, 2.0f, 0.0f));
	g_pEnemy2[0]->x = Enemy2Init + mxE2[0][3];
	g_pEnemy2[0]->y = 3.0f;
	
	if ((g_pEnemy2[0]->x >= 3.0f)) 
	{
		Dir = -1.0f;
		mxInitE2 = Translate(3.0f, 3.0f, 0.0f);
		Enemy2Init = 3.0f;
		g_Enemy2BTime = 0.0f;
		
	}
	else if ((g_pEnemy2[0]->x <= -3.0f)) {
		Dir = 1.0f;
		mxInitE2 = Translate(-3.0f, 3.0f, 0.0f);
		Enemy2Init = -3.0f;
		g_Enemy2BTime = 0.0f;
		
	}	
	if ((g_pEnemy2[0]->Flag == true) && (Bx < g_pEnemy2[0]->x + 0.6f && Bx > g_pEnemy2[0]->x - 0.6f) && (By < g_pEnemy2[0]->y + 0.6f && By > g_pEnemy2[0]->y - 0.6f)) {
		g_pEnemy2[0]->DetectBlood();
		HideB = false;
	}

}

void timer_function(int n){

	if (VBulletNum < 20 && g_Enemy2Time >= 10.0f) {
		/*VShoot(g_pEnemy2[0]->x-0.02,3.0f);*/
		VShoot(g_pEnemy2[0]->x+0.38f, 3.0f);
		VShoot(g_pEnemy2[0]->x - 0.38f, 3.0f);
		
	}
	if (g_pEnemy2[0]->Flag)glutTimerFunc(900, timer_function, 1);
}

void VRShoot() {
	
	VLink = NULL;
	VGetShoot = VHeadShoot;
	while (VGetShoot != NULL) {
		VGetShoot->SetMove();
		if (VGetShoot->GBulletPos() <= -4.0f) {
			if (VLink == NULL) {
				VGet = VGetShoot;
				VHeadShoot = VGetShoot->next;
				VGetShoot = VGetShoot->next;
				VGet->next = VHead;
				VHead = VGet;
			}
			else {
				VGet = VGetShoot;
				VGetShoot = VLink;
				VGetShoot->next = VGet->next;
				VGet->next = VHead;
				VHead = VGet;
			}
			VBulletNum = VBulletNum - 1;
		}
		else {
			VLink = VGetShoot;
			VGetShoot = VGetShoot->next;
		}
	}
	
}

void VShoot(float x1, float y1) {
	if (VHeadShoot == NULL) {
		VHeadShoot = VHead;
		VHead = VHead->next;
		VGetShoot = VHeadShoot;
		VTailShoot = VHeadShoot;
		VGetShoot->next = NULL;
	}
	else {
		VGetShoot = VHead;
		VHead = VHead->next;
		VGetShoot->next = NULL;
		VTailShoot->next = VGetShoot;
		VTailShoot = VGetShoot;
	}
	VGetShoot->GetPos(x1, y1);
	VBulletNum += 1;
	Print(VBulletNum);
}

void RShoot() {
	Link = NULL;
	GetShoot = HeadShoot;
	while (GetShoot != NULL) {
		GetShoot->SetMove();
		
		if (GetShoot->GBulletPos() >= 4.0)  {
			if (Link == NULL) {
				Get = GetShoot;
				HeadShoot = GetShoot->next;
				GetShoot = GetShoot->next;
				Get->next = Head;
				Head = Get;
				By = 0;
			}
			else {
				Get = GetShoot;
				GetShoot = Link;
				GetShoot->next = Get->next;
				Get->next = Head;
				Head = Get;
			}
			BulletCount = BulletCount - 1;
		}
		else {
			Link = GetShoot;
			GetShoot = GetShoot->next;
		}
	}

	

}
void Shoot() {
	HideB = true;
	if (HeadShoot == NULL) {
		HeadShoot = Head;
		Head = Head->next;
		GetShoot = HeadShoot;
		TailShoot = HeadShoot;
		GetShoot->next = NULL;
	}
	else {
		GetShoot = Head;
		Head = Head->next;
		GetShoot->next = NULL;
		TailShoot->next = GetShoot;
		TailShoot = GetShoot;
	}
	GetShoot->GetPos(Pos[0], Pos[1]);
	Bx = GetShoot->mxT[0][3];
	BulletCount += 1;
	Print(BulletCount);

}

void AutomaticRotation(void) {
	mat4 mxRot;

	//glutPostRedisplay();     // 目前的視窗需要被重畫
}
//----------------------------------------------------------------------------

void GL_Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the window
	g_pBG[0]->Draw();
	g_pBG[1]->Draw();
	g_pBG[2]->Draw();
	
	VGetShoot = VHeadShoot;
	while (VGetShoot != NULL) {
		VGetShoot->Draw();
		VGetShoot = VGetShoot->next;
	}

	GetShoot = HeadShoot;
	while (GetShoot != NULL) {
		if(HideB == true)GetShoot->Draw();
		GetShoot = GetShoot->next;
	}

	g_pQuad->Draw();

	if (g_pEnemy1[0]->Flag)g_pEnemy1[0]->Draw();
	if (g_pEnemy1[1]->Flag)g_pEnemy1[1]->Draw();
	if (g_pEnemy1[2]->Flag)g_pEnemy1[2]->Draw();

	if(g_pEnemy2[0]->Flag)g_pEnemy2[0]->Draw();

	
	glutSwapBuffers();	// 交換 Frame Buffer
}

void onFrameMove(float delta)
{
	g_Enemy2Time += delta;
	BgAction(delta);
	Enemy1AutoRotateion(delta);
	if(g_Enemy2Time>10.0f)Enemy2Action(delta);

	VGetShoot = VHeadShoot;
	while (VGetShoot != NULL) {
		VGetShoot->SetMove();
		Eby = VGetShoot->mxT[1][3];
		if (Eby <= -2.0f)VRShoot();
		else VGetShoot = VGetShoot->next;
	}
	//if(g_Enemy2Time > 20.0f){glClearColor(0.96,0.52,0.66, 1.0);}
	//if (g_Enemy2Time > 40.0f) { glClearColor(0.96, 0.46, 0.63, 1.0); }
	GetShoot = HeadShoot;
	while (GetShoot != NULL) {
		GetShoot->SetMove();
		By = GetShoot->mxT[1][3];
		if (By >= 4.0f)RShoot();
		else GetShoot = GetShoot->next;
		/*Print(By);*/
	}

	GL_Display();
}

//----------------------------------------------------------------------------
void reset()
{
	g_iAxis = 2;
	g_fAngle = 0;

	
	g_pQuad->SetTRSMatrix(g_mxModelView);
	/*g_pEnemy1->SetTRSMatrix(g_mxModelView);*/
	glutPostRedisplay();
}
//----------------------------------------------------------------------------

void Win_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case  SPACE_KEY:
		if (VBulletNum < 10) { VShoot(3.0f, 3.0f); }
		break;
	case 68: // D key
	case 100: // d key

		break;
	case 82: // R key
	case 114: // r key
		reset();
		break;
	case 033:
		delete g_pQuad, g_pVBullet, g_pBullet;
		delete g_pEnemy2[0], g_pEnemy2[1];
		delete g_pBG[0], g_pBG[1], g_pBG[2];
		delete g_pEnemy1[0], g_pEnemy1[1], g_pEnemy1[2];
		VGet = VHead;

		while (VGet != NULL) {
			VHead = VGet->next;
			delete(VGet);
			VGet = VHead;
		}
		VGetShoot = VHeadShoot;
		while (VGetShoot != NULL) {
			VHeadShoot = VGetShoot->next;
			delete(VGetShoot);
			VGetShoot = VHeadShoot;
		}
		delete(VHead);
		delete(VHeadShoot);

		Get = Head;

		while (Get != NULL) {
			Head = Get->next;
			delete(Get);
			Get = Head;
		}
		GetShoot = HeadShoot;
		while (GetShoot != NULL) {
			HeadShoot = GetShoot->next;
			delete(GetShoot);
			GetShoot = HeadShoot;
		}
		delete(Head);
		delete(HeadShoot);
		exit(EXIT_SUCCESS);
		break;
	}
}
//----------------------------------------------------------------------------
void Win_Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:   // 目前按下的是滑鼠左鍵
		if (state == GLUT_DOWN) {  // 目前的滑鼠狀態是按住，換成 X 軸
			if (BulletCount < 10)Shoot();HideB = true;g_pEnemy2[0]->BloodFlag = true;// 換軸就重設
		}
		break;
	case GLUT_MIDDLE_BUTTON:  // 目前按下的是滑鼠中鍵 ，換成 Y 軸
		if (state == GLUT_DOWN) {
			if (g_iAxis != 1) { g_iAxis = 1; g_fAngle = 0; }
		}
		break;
	case GLUT_RIGHT_BUTTON:   // 目前按下的是滑鼠右鍵
		if (state == GLUT_DOWN) { // 目前按下的是滑鼠右鍵，換成 Z 軸
			if (g_iAxis != 2) { g_iAxis = 2; g_fAngle = 0; }
		}
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------
void Win_SpecialKeyboard(int key, int x, int y) {


}
void Win_MouseMotion(int x, int y) {

	glutPostRedisplay();     // 目前的視窗需要被重畫
}

//----------------------------------------------------------------------------

void Win_PassiveMotion(int x, int y) {
	mat4 mxGT;

	g_fTx = 4.0f*(x - HALF_SIZE) / (HALF_SIZE);
	g_fTy = -4.0f*(y - HALF_SIZE) / (HALF_SIZE);
	Pos[0] = g_fTx;
	Pos[1] = g_fTy;
	mxGT = Translate(g_fTx, g_fTy, 0);
	g_pQuad->SetTRSMatrix(mxGT);

}

void GL_Reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	/*glEnable(GL_DEPTH_TEST);*/
}

//----------------------------------------------------------------------------

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);

	// If you use freeglut the two lines of code can be added to your application 
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Draw two triangles");

	// The glewExperimental global switch can be turned on by setting it to GL_TRUE before calling glewInit(), 
	// which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	init();


	glutMouseFunc(Win_Mouse);
	glutMotionFunc(Win_MouseMotion);
	glutKeyboardFunc(Win_Keyboard);	// 處理 ASCI 按鍵如 A、a、ESC 鍵...等等
	glutSpecialFunc(Win_SpecialKeyboard);	// 處理 NON-ASCI 按鍵如 F1、Home、方向鍵...等等

	glutDisplayFunc(GL_Display);
	glutReshapeFunc(GL_Reshape);
	glutIdleFunc(IdleProcess);
	glutPassiveMotionFunc(Win_PassiveMotion);
	glutTimerFunc(900,timer_function,1);
	glutMainLoop();
	return 0;
}
