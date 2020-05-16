#ifndef assignment4_functions_h
#define assignment4_functions_h
#endif

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

inline double to_int(std::string const& str) {
	std::istringstream ss(str);
	int d;
	ss >> d;
	if (!(ss && (ss >> std::ws).eof()))
		exit(1);

	return d;
}

inline float to_float(std::string const& str) {
	std::istringstream ss(str);
	float f;
	ss >> f;
	if (!(ss && (ss >> std::ws).eof()))
		exit(1);
	return f;
}

inline char* to_char(string s)
{
	char *a = new char[s.size() + 1];
	a[s.size()] = 0;
	memcpy(a, s.c_str(), s.size());
	return a;
}

void matrix_computation()
{
	Mat Rx, Ry, Rz;
	Mat T;

	Rx.eye();
	Ry.eye();
	Rz.eye();
	T.eye();
	Rx.elem[1][1] = cos(theta_x);
	Rx.elem[1][2] = -sin(theta_x);
	Rx.elem[2][1] = sin(theta_x);
	Rx.elem[2][2] = cos(theta_x);

	Ry.elem[0][0] = cos(theta_y);
	Ry.elem[0][2] = sin(theta_y);
	Ry.elem[2][0] = -sin(theta_y);
	Ry.elem[2][2] = cos(theta_y);

	T.elem[0][3] = translate_x;
	T.elem[1][3] = translate_y;

	Mat P = T * Rx * Ry;

	for (unsigned int i = 0; i < vertice_list.size(); i++)
	{
		Vec current_pt, updated_pt;
		current_pt.elem[0] = vertice_list[i].x;
		current_pt.elem[1] = vertice_list[i].y;
		current_pt.elem[2] = vertice_list[i].z;
		current_pt.elem[3] = 1.0f;
		updated_pt = P * current_pt;
		vertice_list[i].x = updated_pt.elem[0] / updated_pt.elem[3];
		vertice_list[i].y = updated_pt.elem[1] / updated_pt.elem[3];
		vertice_list[i].z = updated_pt.elem[2] / updated_pt.elem[3];

		vertice_list[i].normalize();
	}

	theta_x = 0;
	theta_y = 0;
	theta_z = 0;
	translate_x = 0;
	translate_y = 0;
	translate_z = 0;
}

Vertex normalization(Vertex v)
{
	Vertex output;
	output = v;
	float r = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	output.x = output.x / r;
	output.y = output.y / r;
	output.z = output.z / r;
	return output;
}

void Shading()
{
	if (shading_type == 0)
	{
		for (unsigned int i = 0; i < triangles_list.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					triangles_list[i].c[j].channel[k] = 1.0;

				}
			}
		}
	}
	else if (shading_type == 1)
	{
		for (int i = 0; i < triangles_list.size(); i++)
		{
			Vertex n;
			Vertex n1, n2;
			n1 = vertice_list[triangles_list[i].v_idx[1]] - vertice_list[triangles_list[i].v_idx[0]];
			n2 = vertice_list[triangles_list[i].v_idx[2]] - vertice_list[triangles_list[i].v_idx[1]];
			n1 = normalization(n1);
			n2 = normalization(n2);
			n = n2.crossproduct(n1);
			n = normalization(n);
			Vertex center;
			center = vertice_list[triangles_list[i].v_idx[1]] + vertice_list[triangles_list[i].v_idx[0]] + vertice_list[triangles_list[i].v_idx[2]];
			center.x = center.x / 3.0;
			center.y = center.y / 3.0;
			center.z = center.z / 3.0;
			Vertex l;
			Vertex bc;
			bc.x = teddy_color.channel[0];
			bc.y = teddy_color.channel[1];
			bc.z = teddy_color.channel[2];
			l = center - light;
			Vertex c1;
			c1 = bc;
			float cosin = 0.0;
			l = normalization(l);

			if (l.dotOperator(n) > 0)
				cosin = l.dotOperator(n);
			c1.x = bc.x * ambient_color.channel[0] + light.c.channel[0] * bc.x * cosin;
			c1.y = bc.y * ambient_color.channel[1] + light.c.channel[1] * bc.y * cosin;
			c1.z = bc.z * ambient_color.channel[2] + light.c.channel[2] * bc.z * cosin;
			glColor3f(c1.x, c1.y, c1.z);
			glBegin(GL_TRIANGLES);
			glVertex3f(vertice_list[triangles_list[i].v_idx[0]].x, vertice_list[triangles_list[i].v_idx[0]].y, vertice_list[triangles_list[i].v_idx[0]].z); //point 1
			glVertex3f(vertice_list[triangles_list[i].v_idx[1]].x, vertice_list[triangles_list[i].v_idx[1]].y, vertice_list[triangles_list[i].v_idx[1]].z); //point 2
			glVertex3f(vertice_list[triangles_list[i].v_idx[2]].x, vertice_list[triangles_list[i].v_idx[2]].y, vertice_list[triangles_list[i].v_idx[2]].z); //point 3
			glEnd();
		}
	}
	else if (shading_type == 2)
	{
		for (int i = 0; i < triangles_list.size(); i++)
		{
			Vertex n;
			Vertex n1, n2;
			Vertex v;
			Vertex r;
			v.x = 0;
			v.y = 2;
			v.z = 5;
			n1 = vertice_list[triangles_list[i].v_idx[1]] - vertice_list[triangles_list[i].v_idx[0]];
			n2 = vertice_list[triangles_list[i].v_idx[2]] - vertice_list[triangles_list[i].v_idx[0]];
			n1 = normalization(n1);
			n2 = normalization(n2);
			n = n1.crossproduct(n2);
			n = normalization(n);
			Vertex center;
			center = vertice_list[triangles_list[i].v_idx[1]] + vertice_list[triangles_list[i].v_idx[0]] + vertice_list[triangles_list[i].v_idx[2]];
			center.x = 1.0*center.x / 3.0;
			center.y = 1.0*center.y / 3.0;
			center.z = 1.0*center.z / 3.0;
			Vertex l;
			l = light - center;
			l = normalization(l);
			Vertex bc;
			bc.x = teddy_color.channel[0];
			bc.y = teddy_color.channel[1];
			bc.z = teddy_color.channel[2];
			l = center - light;
			Vertex c1;
			c1 = bc;
			float cosin;
			cosin = n.dotOperator(l);
			r = n * cosin * 2 - l;
			float cosin1 = 0.0;
			if (l.dotOperator(n) > 0)
				cosin1 = l.dotOperator(n);
			float cosin2 = 0.0;
			if (v.dotOperator(r) > 0)
				cosin2 = v.dotOperator(r);
			cosin2 = pow(cosin2, p);
			c1.x = bc.x*ambient_color.channel[0] + light.c.channel[0] * bc.x*cosin1 + light.c.channel[0] * specular_color.channel[0] * cosin2;
			c1.y = bc.y*ambient_color.channel[1] + light.c.channel[1] * bc.y*cosin1 + light.c.channel[1] * specular_color.channel[1] * cosin2;
			c1.z = bc.z*ambient_color.channel[2] + light.c.channel[2] * bc.z*cosin1 + light.c.channel[2] * specular_color.channel[2] * cosin2;
			glColor3f(c1.x, c1.y, c1.z);
			glBegin(GL_TRIANGLES);
			glVertex3f(vertice_list[triangles_list[i].v_idx[0]].x, vertice_list[triangles_list[i].v_idx[0]].y, vertice_list[triangles_list[i].v_idx[0]].z); //point 1
			glVertex3f(vertice_list[triangles_list[i].v_idx[1]].x, vertice_list[triangles_list[i].v_idx[1]].y, vertice_list[triangles_list[i].v_idx[1]].z); //point 2
			glVertex3f(vertice_list[triangles_list[i].v_idx[2]].x, vertice_list[triangles_list[i].v_idx[2]].y, vertice_list[triangles_list[i].v_idx[2]].z); //point 3
			glEnd();
		}

	}
}

void initialize()
{
	light.x = 0;
	light.y = 0;
	light.z = 5;
	light.c.channel[0] = 0.1;
	light.c.channel[1] = 0.1;
	light.c.channel[2] = 0.1;

	light.normalize();

	light.c.channel[0] = 0.3;
	light.c.channel[1] = 0.3;
	light.c.channel[2] = 0.3;

	ambient_color.channel[0] = 0.9;
	ambient_color.channel[1] = 0.9;
	ambient_color.channel[2] = 0.9;

	teddy_color.channel[0] = 1.9;
	teddy_color.channel[1] = 1.7;
	teddy_color.channel[2] = 1.1;

	specular_color.channel[0] = 0.2;
	specular_color.channel[1] = 0.2;
	specular_color.channel[2] = 0.2;
}

void loadObjFiles(const char *filename, vector<Vertex> &vertice_list, vector<Triangle> &triangles_list)
{
	ifstream myfile(filename);
	string line;
	string valueX, valueY, valueZ, v;
	string idx0, idx1, idx2, f;

	int n = 0;
	while (!myfile.eof())
	{
		getline(myfile, line);
		if (line[0] == 'v')
		{
			std::istringstream iss(line);
			iss >> v >> valueX >> valueY >> valueZ;
			Vertex v;
			v.x = (GLfloat)to_float(valueX);
			v.y = (GLfloat)to_float(valueY);
			v.z = (GLfloat)to_float(valueZ);

			for (int c = 0; c < 3; c++)
			{
				v.c.channel[c] = 0.5;
			}
			vertice_list.push_back(v);
		}
		if (line[0] == 'f')
		{
			std::istringstream iss(line);
			iss >> f >> idx0 >> idx1 >> idx2;
			int i0 = to_int(idx0) - 1;
			int i1 = to_int(idx1) - 1;
			int i2 = to_int(idx2) - 1;

			Triangle triangle;
			triangle.v_idx[0] = i0;
			triangle.v_idx[1] = i1;
			triangle.v_idx[2] = i2;

			triangle.c[0] = vertice_list[i0].c;
			triangle.c[1] = vertice_list[i1].c;
			triangle.c[2] = vertice_list[i2].c;
			triangles_list.push_back(triangle);
		}
	}
}
