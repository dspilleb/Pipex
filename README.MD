<h1 align="center">
	📖 Pipex | 19 Brussels
</h1>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/DanNoKenshi/Pipex?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/DanNoKenshi/Pipex?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/DanNoKenshi/Pipex?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/DanNoKenshi/Pipex?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/DanNoKenshi/Pipex?color=green" />
</p>

## 💡 About the project

>This project will let you discover in detail a UNIX mechanism that you already know
>by using it in your program.

## 💻 To use the program 
<h3>you must first compile it with the makefile by using the command 'make' in the shell</h3>

```bash
make all
```

<h3>Then the program must be executed as follows: </h3>

```bash
./pipex file1 cmd1 cmd2 file2
```

<h2> Mandatory </h2>
<h3> It must take 4 arguments:</h3>
<p> <ul>
<li> file1 and file2 are file names.
<li> cmd1 and cmd2 are shell commands with their parameters.
</ul> </p>

------------

<h3>It must behave exactly the same as the shell command below:</h3>

```bash
 < file1 cmd1 | cmd2 > file2
```
<h2> Bonus </h2>
<li> Handle multiple pipes.
<li> Support « and » when the first parameter is "here_doc".

------------

<h3>It must behave exactly the same as the shells command below:</h3>

```bash
 cmd << LIMITER | cmd1 >> file
```
