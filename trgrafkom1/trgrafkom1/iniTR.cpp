#include<Windows.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<Box2D\Box2D.h>


const double PI = 3.14;
const int size = 15;
const int ESCKEY = 27;
bool gravity = true;
b2World* world;



b2Body* addRect(int x, int y, int z, int v, bool dyn){
	b2BodyDef bodydef;
	bodydef.position.Set(x, y);
	if(dyn){
		bodydef.type = b2_dynamicBody;
	}
	b2Body* body = world->CreateBody(&bodydef);
	
	b2PolygonShape shape;
	shape.SetAsBox(z, v);

	b2FixtureDef fixturedef;
	fixturedef.shape=&shape;
	fixturedef.density=1.0;
	body->CreateFixture(&fixturedef);
	return body;
}

b2Body* addCircle(int x, int y, int radius, bool dyn){
	b2BodyDef bodydef;
	bodydef.position.Set(x, y);
	if(dyn){
		bodydef.type = b2_dynamicBody;
	}

	b2Body* body = world->CreateBody(&bodydef);

	b2CircleShape shape;
	shape.m_radius=radius;
	shape.m_p.Set(0,0);

	b2FixtureDef fixturedef;
	fixturedef.shape=&shape;
	fixturedef.density=1.0;
	body->CreateFixture(&fixturedef);
	return body;
}


void drawRect(b2Vec2 points[10], b2Vec2 center, float angle){
	glColor3f(1, 0.715, 0.032);
	glPushMatrix();
	glTranslatef(center.x, center.y, 0);
	glRotatef(angle*180.0/PI, 0, 0, 1);
	glBegin(GL_LINE_LOOP);
	for(int j = 0; j < 4; j++){
		glVertex2f(points[j].x, points[j].y);
	}
	glEnd();
	glPopMatrix();
}


void drawCircle(b2Vec2 center, float radius, float angle){
	glColor3f(0.4, 0.03, 1);
	glPushMatrix();
	glTranslatef(center.x, center.y, 0);
	glRotatef(angle*180/PI, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
		for(int i = 0; i <= 360; i++){
			glVertex2f(cos(i*PI/180.0)*radius, (sin(i*PI/180.0)*radius));
		}
	glEnd();

	glPopMatrix();
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	b2Body* node = world->GetBodyList();
	b2Vec2 points[10];

	while(node){
		if(node->GetFixtureList()->GetShape()->GetType() == b2Shape::e_circle){
			b2CircleShape* circle = (b2CircleShape* ) node->GetFixtureList()->GetShape();
			drawCircle(node->GetWorldCenter(), circle->m_radius, node->GetAngle());
		} else {
			int checkShape = ((b2PolygonShape*)node->GetFixtureList()->GetShape())->GetVertexCount();		
			if (checkShape == 4) {
				for (int k = 0; k < 4; k++) {
					points[k] = ((b2PolygonShape*)node->GetFixtureList()->GetShape())->GetVertex(k);
				}
				drawRect(points, node->GetWorldCenter(), node->GetAngle());				
			}
		}
		node = node->GetNext();
	}

	glutSwapBuffers();
}

void loop (int c){
	world->Step(0.10, 8, 3);
	glutPostRedisplay();
	glutTimerFunc(1, loop, 0);
}

void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0,0,0,1);
	world = new b2World(b2Vec2(0, -9.81));
	glColor3f(1.0, 1.0, 1.0);
	addRect(400, -5, 800, 10, false);
}

void mykeyboard(unsigned char key, int x, int y){
	x = x;
	y = 600 - y;
	switch(key){
	case '1':
		addRect(x, y, size, size, true);
		break;
	case '2':
		addCircle(x, y, size, true);
		break;
	case '3':
		if(gravity){
			glutTimerFunc(1, loop, 0);
			gravity = false;
		}
		break;
	case ESCKEY: 
      exit(0);
      break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glMatrixMode(GL_PROJECTION);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300 ,100);
	glutCreateWindow("TR Tetris");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(mykeyboard);

	glutMainLoop();
	return 0;
}
