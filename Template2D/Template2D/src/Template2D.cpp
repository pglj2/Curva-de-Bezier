/*P2-1: Visualização Interativa das Curvas de Derivadas de Graus até 3:
Descrição: o usuário entra via mouse com os pontos de controle de uma curva de Bézier.
O número de pontos de controle é arbitrário, sem limite. O sistema desenha em 4 janelas
as seguintes curvas: a curva original (controlada pelos pontos do usário), a primeira, a
segunda e a terceira derivadas. O usuário pode modificar o posicionamento dos pontos,
deletar e inserir pontos, e o sistema responder em tempo real de forma adequada,
reconstruindo a curva correspondente. O usuário poderá suprimir os pontos de controle,
a poligonal de controle, e os pontos da curva. O usuário também poderá determinar o
número de avaliações que deverá ser usado para então o sistema calcular os
correspondentes pontos da curva e ligá-los por retas. As avaliações deverão ser feitas
obrigatoriamente com o Algoritmo de de Casteljau para as quatro curvas.*/

#include "Template2D.h"
int Avaliacoes = 1000;
int avalia;
int estado;
GLfloat mouse_x, mouse_y;
GLfloat window_width = 350.0;
GLfloat window_height = 350.0;
Ponto controle[1000];
Ponto controleDerivada1[1000];
Ponto controleDerivada2[1000];
Ponto controleDerivada3[1000];
Ponto pontoCurva[1000];
Ponto pontoDerivada1[1000];
Ponto pontoDerivada2[1000];
Ponto pontoDerivada3[1000];

int qtdControle;
int qtdControleDerivada1 = 0;
int qtdControleDerivada2 = 0;
int qtdControleDerivada3 = 0;
int qtdPonto = 0;
int qtdPontoDerivada1 = 0;
int qtdPontoDerivada2 = 0;
int qtdPontoDerivada3 = 0;
bool colidiu;
bool desenhaBezier;
bool desenhaPrimeira;
bool desenhaSegunda;
bool desenhaTerceira;
bool desenhaPoligonal;
bool desenhaPonto;
int aux = 0;
int window[4];


void myinit()
{
	desenhaBezier = false;
	desenhaPoligonal = true;
	desenhaPonto = true;
	desenhaPrimeira = false;
	desenhaSegunda = false;
	desenhaTerceira = false;
	qtdControle = 0;
	srand(time(NULL));
	estado = MODIFIED;
	loop(0);
}

void myreshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	window_width = (GLfloat)w;
	window_height = (GLfloat)h;
	glOrtho(0, window_width, 0, window_height, -1.0, -1.0);
}


// Função que utiliza o algoritmo de De Casteljau montarmos a curva de Bezier
Ponto algoritmoDeCasteljau(float T, int Control, Ponto controleArray[], int j) {

	Ponto Retorno;
	Ponto temp1;
	Ponto temp2;

	//caso base
	if (Control == 0) {
		Retorno = controleArray[j];
		return Retorno;
	}
	else {

		//Caso Recursivo
		temp1 = algoritmoDeCasteljau(T, Control - 1, controleArray, j);
		temp2 = algoritmoDeCasteljau(T, Control - 1, controleArray, j + 1);

		Retorno.x = ((temp1.x) * (1 - T)) + ((temp2.x) * T);
		Retorno.y = ((temp1.y) * (1 - T)) + ((temp2.y) * T);

		return Retorno;
	}
}


// funcão apenas para calcular a diferença do ponto e de seu anterior;
Ponto difer(Ponto p1, Ponto p2) {
	Ponto Ret;
	Ret.x = p2.x - p1.x;
	Ret.y = p2.y - p1.y;
	return Ret;
}



//função pra detectar se teve "colisão" de pontos
bool colisaoPonto(int x, int y, Ponto p)
{
	mouse_x = ((((GLfloat)x) / window_width)*2.0) - 1.0;
	mouse_y = -(((((GLfloat)y) / window_height)*2.0) - 1.0);
	GLfloat m = 0.1;
	bool b = (((mouse_x >= (p.x - m)) && (mouse_x <= (p.x + m))) && ((mouse_y >= (p.y - m)) && (mouse_y <= (p.y + m))));
	return b;
}
//função para realocar vetor de ponto de controle
void removerPontoControle(int x, int y, int index) {
	int aux = qtdControle - index - 1;
	qtdControle--;
	for (int i = 0; i < aux; i++) {
		controle[index + i] = controle[index + i + 1];
	}
}





void mydisplay1() { //função secundária ao display da janela principal para desenhar a curva da 1ª derivada
	glutSetWindow(window[1]);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < qtdControle; i++) {
		for (int i = 0; i < qtdPonto - 3; i++) {
			glBegin(GL_LINES);
			glVertex2f(pontoDerivada1[i].x, pontoDerivada1[i].y);
			glVertex2f(pontoDerivada1[i + 1].x, pontoDerivada1[i + 1].y);
			glEnd();
		}
		glutSetWindow(window[0]);
	}

}

void mydisplay2() {
	// função secundária ao display da janela principal para desenhar a curva da 2ª derivada
	glutSetWindow(window[2]);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < qtdControle; i++) {
		for (int i = 0; i < qtdPonto - 4; i++) {
			glBegin(GL_LINES);
			glVertex2f(pontoDerivada2[i].x, pontoDerivada2[i].y);
			glVertex2f(pontoDerivada2[i + 1].x, pontoDerivada2[i + 1].y);
			glEnd();
		}
		glutSetWindow(window[0]);
	}

}

void mydisplay3() {
	glutSetWindow(window[3]);
	//função secundária ao display da janela principal para desenhar a curva da 3ª derivada
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < qtdControle; i++) {
		for (int i = 0; i < qtdPonto - 5; i++) {
			glBegin(GL_LINES);
			glVertex2f(pontoDerivada3[i].x, pontoDerivada3[i].y);
			glVertex2f(pontoDerivada3[i + 1].x, pontoDerivada3[i + 1].y);
			glEnd();
		}
		glutSetWindow(window[0]);
	}

}



void mydisplay()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < qtdControle; i++) { //pontos
		glColor3f(0, 0, 0); // cor dos pontos
		glPointSize(3.0f); // tamanho dos pontos
		if (desenhaPonto) {
			glBegin(GL_POINTS);
			glVertex2f(controle[i].x, controle[i].y);
			glEnd();
		}

		if (desenhaPoligonal) {
			if (qtdControle > 1) {
				if (i > 0) {
					glBegin(GL_LINES); //poligonal
					glVertex2f(controle[i - 1].x, controle[i - 1].y);
					glVertex2f(controle[i].x, controle[i].y);
					glEnd();
				}
			}
		}
		//Curva de Bezier
		if ((qtdControle > 2) && (estado != IDLE)) {
			qtdPonto = 0;
			int j = 0;
			for (float t = 0; t <= 1.0; t += (1 / (float)(Avaliacoes))) {
				pontoCurva[qtdPonto++] = algoritmoDeCasteljau(t, qtdControle - 1, controle, j);

			}
			desenhaBezier = true;
		}

		if (qtdControle <= 2) desenhaBezier = false;

		if (desenhaBezier && (glutGetWindow() == window[0])) {
			for (int i = 0; i < qtdPonto - 2; i++) {
				glBegin(GL_LINES);
				glVertex2f(pontoCurva[i].x, pontoCurva[i].y);
				glVertex2f(pontoCurva[i + 1].x, pontoCurva[i + 1].y);
				glEnd();
			}
		}

		//Derivada1

		if ((qtdControle > 3) && (estado != IDLE)) {
			for (int l = 0; l <= qtdControle - 2; l++) {
				controleDerivada1[l] = difer(controle[l], controle[l + 1]);
			}

			qtdPontoDerivada1 = 0;
			int u = 0;
			for (float t = 0; t <= 1.0; t += (1 / (float)(Avaliacoes))) {
				pontoDerivada1[qtdPontoDerivada1++] = algoritmoDeCasteljau(t, qtdControle - 2, controleDerivada1, u);
			}
			desenhaPrimeira = true;
		}

		if (qtdControle <= 3) desenhaPrimeira = false;

		if (desenhaPrimeira) {
			glutSetWindow(window[1]);
			mydisplay1();
			glutSetWindow(window[0]);
		}


		//Derivada2
		if ((qtdControle > 4) && (estado != IDLE)) {
			for (int l = 0; l <= qtdControle - 4; l++) {
				controleDerivada2[l] = difer(controleDerivada1[l], controleDerivada1[l + 1]);
			}

			qtdPontoDerivada2 = 0;
			int v = 0;
			for (float t = 0; t <= 1.0; t += (1 / (float)(Avaliacoes))) {
				pontoDerivada2[qtdPontoDerivada2++] = algoritmoDeCasteljau(t, qtdControle - 3, controleDerivada2, v);
			}
			desenhaSegunda = true;
		}
		if (qtdControle <= 4) desenhaSegunda = false;

		if (desenhaSegunda) {
			glutSetWindow(window[2]);
			mydisplay2();
			glutSetWindow(window[0]);
		}

		//Derivada3
		if ((qtdControle > 5) && (estado != IDLE)) {

			for (int l = 0; l <= qtdControle - 4; l++) {
				controleDerivada3[l] = difer(controleDerivada2[l], controleDerivada2[l + 1]);
			}

			qtdPontoDerivada3 = 0;
			int w = 0;
			for (float t = 0; t <= 1.0; t += (1 / (float)(Avaliacoes))) {
				pontoDerivada3[qtdPontoDerivada3++] = algoritmoDeCasteljau(t, qtdControle - 4, controleDerivada3, w);
			}
			desenhaTerceira = true;
		}
		if (qtdControle <= 5) desenhaTerceira = false;

		if (desenhaTerceira) {
			glutSetWindow(window[3]);
			mydisplay3();
			glutSetWindow(window[0]);
		}

	}

	glFlush();
}



void handleMotion(int x, int y)
{
	if ((estado != MODIFIED) && (estado != IDLE)) {
		controle[estado].x = (((((GLfloat)x) / window_width)*2.0) - 1.0) + mouse_x;
		controle[estado].y = (-(((((GLfloat)y) / window_height)*2.0) - 1.0)) + mouse_y;
	}
}



//x e y sao as coordenas onde cliquei na tela
//mouse_x e mouse_y eh onde cliquei so que ele converte pra as coordenadas de tela do OpenGL
void handleMouse(int btn, int state, int x, int y)
{
	if (estado == IDLE && btn == GLUT_LEFT_BUTTON) {
		mouse_x = ((((GLfloat)x) / window_width)*2.0) - 1.0;
		mouse_y = -(((((GLfloat)y) / window_height)*2.0) - 1.0);

		if (state == GLUT_DOWN) {
			for (int i = qtdControle - 1; i >= 0; i--) {
				if ((mouse_x >= (controle[i].x - 0.1)) && (mouse_y >= (controle[i].y) - 0.1) && (mouse_x <= (controle[i].x + 0.1)) && (mouse_y <= (controle[i].y + 0.1))) {
					mouse_x = controle[i].x - mouse_x;
					mouse_y = controle[i].y - mouse_y;
					estado = i;
					break;
				}
			}
		}
	}
	else if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		estado = MODIFIED;
	}
	else if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) { //remoção de pontos
		//a colisão nesse caso seria colocar o cursor sobre a localização de um determinado ponto
		colidiu = false;
		int k;
		int balao;
		for (k = 0; k < qtdControle && !colidiu; k++) {
			colidiu = colisaoPonto(x, y, controle[k]);
			if (colidiu) balao = k;
		}
		if (colidiu) {
			removerPontoControle(x, y, balao);
			estado = MODIFIED;
		}

	}
	else if (estado == IDLE && btn == GLUT_RIGHT_BUTTON) {
		//inserção de pontos
		//verifica se o usuário tenta criar um ponto muito próximo do outro a fim de se ter uma visão melhor da curva
		//e da poligonal
		if (state == GLUT_DOWN) {
			colidiu = false;
			for (int k = 0; k < qtdControle && !colidiu; k++) {
				colidiu = colisaoPonto(x, y, controle[k]);
			}
			if (!colidiu) {
				GLfloat x2 = ((((GLfloat)x) / window_width)*2.0) - 1.0;
				GLfloat y2 = -(((((GLfloat)y) / window_height)*2.0) - 1.0);
				controle[qtdControle++] = Ponto(x2, y2);
				estado = MODIFIED;
			}
		}
	}
}

void hadleKeyboard(unsigned char key, int x, int y)
{
	if (key == ESC) {
		exit(0);
	}
}

void hadleSpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F5) {
		myinit();
	}

	if (key == GLUT_KEY_F2) {
		desenhaPonto = !desenhaPonto;
		mydisplay();
	}

	if (key == GLUT_KEY_F3) {
		desenhaPoligonal = !desenhaPoligonal;
		mydisplay();
	}

	if (key == GLUT_KEY_F4) {
		glutSetWindow(window[0]);
		desenhaBezier = !desenhaBezier;
		mydisplay();
	}

}

void loop(int id)
{
	if (estado == MODIFIED) {
		mydisplay();
		estado = IDLE;
	}
	else if (estado != IDLE) {
		mydisplay();
	}
	glutTimerFunc(1000 / FPS, loop, id);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(window_width, window_height);
	window[0] = glutCreateWindow("ProjetoPG");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutMouseFunc(handleMouse);
	glutMotionFunc(handleMotion);
	glutKeyboardUpFunc(hadleKeyboard);
	glutSpecialUpFunc(hadleSpecialKeyboard);

	window[1] = glutCreateWindow("Primeira");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);

	window[2] = glutCreateWindow("Segunda");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);

	window[3] = glutCreateWindow("Terceira");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);

	myinit();

	glutMainLoop();
	return 0;
}
