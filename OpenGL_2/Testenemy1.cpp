#include "./Testenemy1.h"

Enemy11::Enemy11()
{
	m_Points[0] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Points[1] = vec4(0.1f, 0.2f, 0.0f, 1.0f);
	m_Points[2] = vec4(0.0f, 0.3f, 0.0f, 1.0f); //1
	m_Points[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Points[4] = vec4(0.0f, 0.3f, 0.0f, 1.0f);
	m_Points[5] = vec4(-0.1f, 0.2f, 0.0f, 1.0f);//2
	m_Points[6] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Points[7] = vec4(-0.2f, 0.1f, 0.0f, 1.0f);
	m_Points[8] = vec4(-0.3f, 0.0f, 0.0f, 1.0f);//3
	m_Points[9] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Points[10] = vec4(-0.3f, 0.0f, 0.0f, 1.0f);
	m_Points[11] = vec4(-0.2f, -0.1f, 0.0f, 1.0f);//4
	m_Points[12] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Points[13] = vec4(-0.1f, -0.2f, 0.0f, 1.0f);
	m_Points[14] = vec4(0.0f, -0.3f, 0.0f, 1.0f);//5
	m_Points[15] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Points[16] = vec4(0.0f, -0.3f, 0.0f, 1.0f);
	m_Points[17] = vec4(0.1f, -0.2f, 0.0f, 1.0f);//6
	m_Points[18] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Points[19] = vec4(0.2f, -0.1f, 0.0f, 1.0f);
	m_Points[20] = vec4(0.3f, 0.0f, 0.0f, 1.0f);//7
	m_Points[21] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Points[22] = vec4(0.3f, 0.0f, 0.0f, 1.0f);
	m_Points[23] = vec4(0.2f, 0.1f, 0.0f, 1.0f);//8





	m_Colors[0] = vec4(1.0f, 1.0f, 1.0f, 1.0f);  // (r, g, b, a)
	m_Colors[1] = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_Colors[2] = vec4(1.0f, 1.0f, 0.0f, 1.0f);//1
	m_Colors[3] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Colors[4] = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_Colors[5] = vec4(1.0f, 0.0f, 1.0f, 1.0f);//2
	m_Colors[6] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Colors[7] = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_Colors[8] = vec4(1.0f, 1.0f, 0.0f, 1.0f);//3
	m_Colors[9] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Colors[10] = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_Colors[11] = vec4(1.0f, 0.0f, 1.0f, 1.0f);//4
	m_Colors[12] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Colors[13] = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_Colors[14] = vec4(1.0f, 1.0f, 0.0f, 1.0f);//5
	m_Colors[15] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Colors[16] = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_Colors[17] = vec4(1.0f, 0.0f, 1.0f, 1.0f);//6
	m_Colors[18] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Colors[19] = vec4(1.0f, 0.0f, 1.0f, 1.0f);
	m_Colors[20] = vec4(1.0f, 1.0f, 0.0f, 1.0f);//7
	m_Colors[21] = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Colors[22] = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	m_Colors[23] = vec4(1.0f, 1.0f, 0.0f, 1.0f);//8
	/*Create and initialize a buffer object */
	CreateBufferObject();
	m_bUpdateProj = false;
}


void Enemy11::CreateBufferObject()
{
	glGenVertexArrays(1, &m_uiVao);
	glBindVertexArray(m_uiVao);

	// Create and initialize a buffer object

	glGenBuffers(1, &m_uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Points) + sizeof(m_Colors), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_Points), m_Points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_Points), sizeof(m_Colors), m_Colors);
}

void Enemy11::SetShader(mat4 &mxView, mat4 &mxProjection, GLuint uiShaderHandle)
{
	// Load shaders and use the resulting shader program
	if (uiShaderHandle == MAX_UNSIGNED_INT) m_uiProgram = InitShader("vsVtxColor.glsl", "fsVtxColor.glsl");
	else m_uiProgram = uiShaderHandle;

	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(m_uiProgram, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(m_uiProgram, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(m_Points)));

	m_uiModelView = glGetUniformLocation(m_uiProgram, "ModelView");
	m_mxView = mxView;
	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxView);

	m_uiProjection = glGetUniformLocation(m_uiProgram, "Projection");
	m_mxProjection = mxProjection;
	glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);
	m_uiMove = glGetUniformLocation(m_uiProgram, "mxS"); //新增shader 要加這行!
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Enemy11::SetViewMatrix(mat4 &mat)
{
	m_mxView = mat;
	m_bUpdateMV = true;
}

void Enemy11::SetProjectionMatrix(mat4 &mat)
{
	m_mxProjection = mat;
	m_bUpdateProj = true;
}

void Enemy11::SetTRSMatrix(mat4 &mat)
{
	m_mxTRS = mat;
	m_bUpdateMV = true;
}

void Enemy11::SetColor(GLfloat vColor[4])
{
	for (int i = 0; i < 6; i++) {
		m_Colors[i].x = vColor[0];
		m_Colors[i].y = vColor[1];
		m_Colors[i].z = vColor[2];
		m_Colors[i].w = vColor[3];
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_Points), sizeof(m_Colors), m_Colors);
}

void Enemy11::SetVtxColors(GLfloat vLFColor[], GLfloat vLRColor[], GLfloat vTRColor[], GLfloat vTLColor[])
{
	m_Colors[0].x = vLFColor[0];
	m_Colors[0].y = vLFColor[1];
	m_Colors[0].z = vLFColor[2];
	m_Colors[0].w = vLFColor[3];
	m_Colors[3] = m_Colors[0];

	m_Colors[1].x = vLRColor[0];
	m_Colors[1].y = vLRColor[1];
	m_Colors[1].z = vLRColor[2];
	m_Colors[1].w = vLRColor[3];

	m_Colors[2].x = vTRColor[0];
	m_Colors[2].y = vTRColor[1];
	m_Colors[2].z = vTRColor[2];
	m_Colors[2].w = vTRColor[3];
	m_Colors[4] = m_Colors[2];

	m_Colors[5].x = vTLColor[0];
	m_Colors[5].y = vTLColor[1];
	m_Colors[5].z = vTLColor[2];
	m_Colors[5].w = vTLColor[3];

	glBindBuffer(GL_ARRAY_BUFFER, m_uiBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(m_Points), sizeof(m_Colors), m_Colors);
}

void Enemy11::Draw()
{
	glUseProgram(m_uiProgram);
	glBindVertexArray(m_uiVao);
	if (m_bUpdateMV) {
		m_mxMVFinal = m_mxView*m_mxTRS;
		m_bUpdateMV = false;
	}
	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxMVFinal);

	if (m_bUpdateProj) {
		glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);
		m_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, 24);

}

void Enemy11::DrawW()
{
	glBindVertexArray(m_uiVao);

	if (m_bUpdateMV) {
		m_mxMVFinal = m_mxView*m_mxTRS;
		m_bUpdateMV = false;
	}

	glUniformMatrix4fv(m_uiModelView, 1, GL_TRUE, m_mxMVFinal);
	if (m_bUpdateProj) {
		glUniformMatrix4fv(m_uiProjection, 1, GL_TRUE, m_mxProjection);
		m_bUpdateProj = false;
	}
	glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM);
}
