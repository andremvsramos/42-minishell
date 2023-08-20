# 42-minishell

Recreation of the original shell.\
Grade: 101/100 (+25 Bonus);

## Overview

- Bonus points were earned for correctly implementing the handling of `"${USER}"` expansions without expansion.
- The project does not need to handle specific cases such as pipes at the end of a command line, similar to the original bash/shell behavior.

## Features

- Almost all original shell functionality has been recreated, except for these handlers: `&&`, `||`, `<<<`, `<>`, `>|`.
- Built-in commands implemented from the ground up: `cd`, `pwd`, `echo`, `exit`, `env`, `export`, `unset`.
- Any other commands are executed using `execve`.
- Minishell project copies the system environment variables to a new list, ensuring it does not affect the user's own system environment variables.

## Collaborator

This project was made in collaboration with Tiago Pereira ([@t-pereira06](https://github.com/t-pereira06)). Please consider giving credit to him for his contribution.

## Usage

1. Run the `make` command to compile the project.
2. Execute the shell by running `./minishell`.

## Notes

- The project uses fsanitizer in thread mode to analyze leaks.
- Using valgrind exposes readline library leaks, though this is not a problem solved by the project.
- There's a random leak caused by readline's `add_history` function, which is also not the project's responsibility to solve.

## License

- This project was made as part of the 42 Porto curriculum.
