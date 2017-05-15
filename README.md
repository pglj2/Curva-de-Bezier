Processamento Gráfico - if680 - 2016.1
Alunos: Milena Santos Cabral Carneiro (mscc)
		Paulo Gustavo Lasalvia Jorge (pglj2)
-----------------------------------------------------------------------------

Funcionalidades:
1-	Criar um ponto preto ao clicar com o botão
direito do mouse. A posição é definida pela posição atual do mouse.
2-	Movimentar o ponto segurando o botão esquerdo do mouse e arrastando, modificando uma curva (e suas derivadas), 
caso alguma esteja desenhada, em tempo real.
3-	Limpar a tela apertando a tecla F5.
4-	Sair do programa apertando a tecla ESC.
5-  Deletar um ponto ao clicar com o botão do meio do mouse (roll).
6-  Suprimir ou não os pontos ao apertar F2.
7-  Suprimir ou não a poligonal ao apertar F3.
8-  Suprimir ou não a curva de Bézier ao apertar F4.

Observações:
	Para as curvas das derivadas aparecerem, é necessário escolher qual(is) das janelas (nomeadas
"Primeira", "Segunda" e "Terceira", representando qual grau da derivada correspondem) e maximizá-las. 
Nessas janelas, as curvas irão se modificar de acordo com a manipulação dos pontos da janela principal (nomeada "Projeto PG").
Cada curva de derivada deve aparecer conforme uma quantidade mínima de pontos para cada.

Referências:
Funcoes de C/C++:
http://www.cplusplus.com/
Copia online do Red Book (OpenGL Programming Guide):
http://fly.cc.fer.hr/~unreal/theredbook/
Referencia online para os comandos OpenGL (Man pages):
http://www.opengl.org/sdk/docs/man/
http://stackoverflow.com/questions/10465462/multiple-windows-opengl-glut
Algoritmo de de Casteljau: 
http://www.malinc.se/m/DeCasteljauAndBezier.php
http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/de-casteljau.html
Livro "Curves and Surfaces for CAGD: A Practical Guide" do autor Gerard Farin - 5ª edição - 2001