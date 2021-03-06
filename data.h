#ifndef assignment4_data_h
#define assignment4_data_h


#endif

#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

struct Color {
	GLfloat channel[3];
};

struct Vertex {
	float x;
	float y;
	float z;
	Color c;
	float uni_x;
	float uni_y;
	float uni_z;

	void normalize()
	{
		float len = x * x + y * y + z * z;
		uni_x = x / sqrt(len);
		uni_y = y / sqrt(len);
		uni_z = z / sqrt(len);
	}

	const Vertex operator * (const Vertex right) const
	{
		Vertex result;
		result.x = x * right.x;
		result.y = y * right.y;
		result.z = z * right.z;
		return result;
	}

	const Vertex operator * (const float right) const
	{
		Vertex result;
		result.x = x * right;
		result.y = y * right;
		result.z = z * right;
		return result;
	}

	const Vertex operator - (const Vertex& right) const
	{
		Vertex result;

		result.x = x - right.x;
		result.y = y - right.y;
		result.z = z - right.z;

		return result;
	}

	const Vertex operator - (const float& right) const
	{
		Vertex result;
		result.x = x - right;
		result.y = y - right;
		result.z = z - right;

		return result;
	}

	const Vertex operator + (const Vertex& right) const
	{
		Vertex result;
		result.x = x + right.x;
		result.y = y + right.y;
		result.z = z + right.z;
		return result;
	}

	float dotOperator(const Vertex& right) const
	{
		float r;
		r = 1.0*x*right.x + 1.0*y*right.y + 1.0*z*right.z;

		return r;
	}

	Vertex crossproduct(const Vertex& right)
	{
		Vertex result;
		result.x = y * right.z - z * right.y;
		result.y = z * right.x - x * right.z;
		result.z = x * right.y - y * right.x;

		return result;
	}
};

struct Triangle {
	int v_idx[3];
	Vertex v1, v2, v3;
	Vertex V1, V2;
	Color c[3];
	Vertex n;

	void Normal()
	{
		V1 = v2 - v1;
		V2 = v3 - v1;
		n = V1 * V2;
	}
};

struct Vec {
	float elem[4];
};

struct Mat {
	float elem[4][4];
	void eye()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
					elem[i][j] = 1.0f;
				else
					elem[i][j] = 0.0f;
			}
		}
	}

	const Mat operator * (const Mat& right) const
	{
		Mat result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.elem[i][j] = 0;
				for (int k = 0; k < 4; k++)
				{
					result.elem[i][j] += elem[i][k] * right.elem[k][j];
				}
			}
		}

		return result;
	}

	const Vec operator * (const Vec& vec) const
	{
		Vec result;

		for (int i = 0; i < 4; i++)
		{

			result.elem[i] = 0;
			for (int k = 0; k < 4; k++)
			{
				result.elem[i] += elem[i][k] * vec.elem[k];
			}

		}

		return result;
	}

	void print()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				printf("%.5f, ", elem[i][j]);
			}
			printf("\n");
		}
	}
};


vector<Vertex> vertice_list;
vector<Triangle> triangles_list;

Vertex light;
Color ambient_color;
Color teddy_color;
Color specular_color;
int p = 0.8;

float theta_x = .0f;
float theta_y = .0f;
float theta_z = .0f;
float translate_x = .0f;
float translate_y = .0f;
float translate_z = .0f;


int mesh_only = 0;
int shading_type = 0;

int mouse_down = 0;
int change_mode = 0;
int current_x = 0, current_y = 0;

