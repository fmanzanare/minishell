# Minishell — custom shell in C

`Minishell` is a custom **Unix-like shell written in C** as part of the **42** curriculum. The project focuses on implementing the core mechanics behind an interactive shell: **prompt handling**, **syntax validation**, **quote-aware parsing**, **environment expansion**, **pipes**, **redirections**, **here-documents**, **builtin commands**, **PATH resolution**, and **process execution**.

From an engineering perspective, this repository demonstrates low-level systems fundamentals: how command lines are parsed, how shell state is preserved across commands, how file descriptors are redirected, how child processes are created, and how builtins and external executables are dispatched from a single interactive loop.

## What the project includes

- An interactive shell loop built around **Readline**
- Quote-aware **syntax checking** before execution
- Command parsing into an internal linked-list representation
- **Environment variable expansion**, including `$?`
- Support for **pipes**, input/output redirections, append redirections, and **here-documents**
- Builtins for:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Execution of external programs through **fork + execve**
- Command lookup through the shell `PATH`
- Signal handling tailored for an interactive shell experience

## Architecture at a glance

### Runtime flow

- `src/minishell.c` runs the main interactive loop
- each prompt input is validated for syntax before parsing (`src/syntax_errors/syntax_checker.c`)
- the parser expands variables, normalizes separators, splits pipelines, and fills a command list (`src/list/parser.c`, `src/utils/pipes_and_redirs.c`, `src/expander/expander.c`)
- the execution layer prepares file descriptors, builtins, pipes, here-docs, and child processes (`src/terminator/terminator.c`, `src/terminator/redirections.c`, `src/terminator/hd_utils.c`)
- environment state is maintained across commands through internal structures initialized in `src/terminator/init.c`

### Main components

- `src/minishell.c` — prompt loop, syntax gate, parser/executor orchestration
- `src/syntax_errors/` — syntax validation for pipes, redirections, quotes, and unsupported tokens
- `src/expander/` — environment variable expansion
- `src/list/` — parser helpers and internal command representation building
- `src/terminator/` — execution layer, builtins, signal handling, redirections, here-docs, PATH resolution
- `src/utils/` — tokenization, quote handling, pipe/redirection preprocessing, cleanup helpers
- `includes/minishell.h` — shared structures and function declarations

## Supported capabilities

### Interactive shell behavior
- prompt-based input with **Readline** (`src/minishell.c`)
- command history through Readline integration (`src/minishell.c`, `Makefile`)
- interactive signal behavior for `Ctrl+C` and ignored `SIGQUIT` in the main shell loop (`src/terminator/signal.c`, `src/terminator/init.c`)

### Parsing and syntax handling
- detection of syntax errors around pipes and redirections (`src/syntax_errors/syntax_checker.c`)
- detection of unclosed single or double quotes (`src/syntax_errors/syntax_checker.c`)
- quote-aware parsing so separators inside quotes are not treated as shell operators (`src/syntax_errors/syntax_checker.c`, `src/utils/pipes_and_redirs.c`)
- splitting of pipeline segments and command structures into internal linked-list nodes (`src/list/parser.c`, `includes/minishell.h`)

### Expansion and environment handling
- expansion of environment variables (`$VAR`) (`src/expander/expander.c`)
- expansion of the previous exit status through `$?` (`src/expander/expander.c`)
- internal linked-list environment model plus synchronized `envp` array for execution (`src/terminator/init.c`, `src/terminator/list.c`)
- builtin support for modifying shell state through `export`, `unset`, and `cd` (`src/terminator/builtins/export.c`, `src/terminator/builtins/unset.c`, `src/terminator/builtins/cd.c`)

### Execution model
- builtin command dispatch for shell-resident behavior (`src/terminator/terminator.c`)
- external command execution through `fork()` and `execve()` (`src/terminator/terminator.c`)
- executable lookup through `PATH` resolution (`src/terminator/parserpath.c`)
- pipeline-oriented execution across multiple parsed commands (`src/terminator/terminator.c`)
- file descriptor setup for command input/output redirections (`src/terminator/redirections.c`)
- here-document support (`src/terminator/hd_utils.c`)

## Builtin commands

The current implementation includes these builtins:

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

See `src/terminator/builtins/`.

## Tech stack

| Layer | Technology |
|---|---|
| Language | C |
| Input handling | Readline |
| Process model | `fork`, `execve`, `waitpid` |
| Terminal/signals | POSIX signals + `termios` |
| Build | Make |
| Utility layer | bundled `libft_plus` + `ft_printf` |

## Why this project matters technically

This repository is relevant beyond the academic exercise because it demonstrates several systems concerns that remain useful in backend and platform engineering:

- **interactive CLI runtime behavior**
- **shell-style parsing and token handling**
- **environment propagation and mutation**
- **PATH-based command resolution**
- **process spawning and child lifecycle management**
- **file descriptor redirection and pipeline composition**
- **signal handling in interactive programs**

In short, it shows how a shell coordinates parsing, state, redirections, and execution without delegating that behavior to an existing shell implementation.

## Project structure

```text
.
├── includes/                 # Main header + libft_plus support library
├── src/
│   ├── expander/            # Environment variable expansion
│   ├── list/                # Parser and command-structure building
│   ├── syntax_errors/       # Syntax checking
│   ├── terminator/          # Execution layer, builtins, signals, redirections
│   └── utils/               # Splitting, quote handling, cleanup helpers
├── Makefile
└── src/minishell.c          # Program entrypoint
```

## Build and run

### Requirements
- `gcc`
- `make`
- `readline`

### Build
```bash
make
```

### Run
```bash
./minishell
```

## Build note

The current `Makefile` is wired to a local Readline installation under a Homebrew-style path:

- `-I /Users/$(USER)/.brew/opt/readline/include`
- `-L /Users/$(USER)/.brew/opt/readline/lib -lreadline`

So if you build it on another machine, you may need to adjust the Readline include/library paths in `Makefile`.

## Scope note

This README intentionally describes the **actual capabilities visible in the codebase**. It does not present Minishell as a complete POSIX shell or as a drop-in replacement for `bash` or `zsh`. Its value lies in the implementation of **shell parsing**, **environment handling**, **process execution**, **redirections**, and **interactive terminal behavior** built from first principles.
