#ifndef assignment_4_callbackFunction_h
#define assignment_4_callbackFunction_h
#endif

void onKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(1);
		break;
	case 'm':
		mesh_only = (mesh_only == 1) ? 0 : 1;
		glutPostRedisplay();
		break;
    case '1':
            shading_type = 1;
            teddy_color.channel[0] = 0.9;
            teddy_color.channel[1] = 0.7;
            teddy_color.channel[2] = 0.1;
            glutPostRedisplay();
            break;
        case '2':
            shading_type = 2;
            teddy_color.channel[0] = 0.9;
            teddy_color.channel[1] = 0.7;
            teddy_color.channel[2] = 0.1;
            glutPostRedisplay();
            break;
        case '3':
            shading_type = 3;
            teddy_color.channel[0] = 0.9;
            teddy_color.channel[1] = 0.7;
            teddy_color.channel[2] = 0.1;
            glutPostRedisplay();
            break;
	default:
		break;
	}
}


void onMouse(int button, int state, int x, int y)
{

	GLint specialKey = glutGetModifiers();
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			mouse_down = 1;
			current_x = x;
			current_y = y;
			if (specialKey == GLUT_ACTIVE_SHIFT)
			{
				change_mode = 1;
			}
			else
			{
				change_mode = 0;
			}
		}
		else if (state == GLUT_UP)
		{
			mouse_down = 0;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			break;
	default:
		break;
	}
}

void onMouseMotion(int x, int y)
{
	if (mouse_down == 1)
	{
		if (change_mode == 0)
		{
			theta_y += static_cast<float>(x - current_x) / 100.f;
			theta_x += static_cast<float>(y - current_y) / 100.f;
		}
		else {
			translate_x += static_cast<float>(x - current_x) / 1000.f;
			translate_y += static_cast<float>(-y + current_y) / 1000.f;
		}

		current_x = x;
		current_y = y;
	}
	glutPostRedisplay();
}
void renderAllTriangles()
{
	for (int i = 0; i < triangles_list.size(); i++)
	{
		if (mesh_only)
		{
			glBegin(GL_LINE_LOOP);
		}
		else
		{
			glBegin(GL_TRIANGLES);
		}

		int pt_0 = triangles_list[i].v_idx[0];
		int pt_1 = triangles_list[i].v_idx[1];
		int pt_2 = triangles_list[i].v_idx[2];

		glColor3f(triangles_list[i].c[0].channel[0], triangles_list[i].c[0].channel[1], triangles_list[i].c[0].channel[2]);
		glVertex3f(vertice_list[pt_0].x, vertice_list[pt_0].y, vertice_list[pt_0].z);

		glColor3f(triangles_list[i].c[1].channel[0], triangles_list[i].c[1].channel[1], triangles_list[i].c[1].channel[2]);
		glVertex3f(vertice_list[pt_1].x, vertice_list[pt_1].y, vertice_list[pt_1].z);

		glColor3f(triangles_list[i].c[2].channel[0], triangles_list[i].c[2].channel[1], triangles_list[i].c[2].channel[2]);
		glVertex3f(vertice_list[pt_2].x, vertice_list[pt_2].y, vertice_list[pt_2].z);
		glEnd();
	}
}

void onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);

	if (mouse_down == 1)
		matrix_computation();
	Shading();
	renderAllTriangles();
	printf("light: %.3f, %.3f, %.3f\n", light.x, light.y, light.z);
	glFlush();
}
