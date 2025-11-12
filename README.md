# Pipex

This project recreates the behavior of the shell pipeline (`|`) and redirections (`<`, `>`). It handles process creation, execution, and inter-process communication using pipes, mimicking the `$ < file1 cmd1 | cmd2 > file2` command.

## 🔧 Key Concepts
- Process forking (`fork`)
- Inter-process communication with pipes (`pipe`)
- File descriptor manipulation (`dup2`)
- Command execution (`execve`)
- Path resolution and command lookup

## 🚀 Usage
./pipex file1 "cmd1" "cmd2" file2

-> Equivalent to: < file1 cmd1 | cmd2 > file2
    
