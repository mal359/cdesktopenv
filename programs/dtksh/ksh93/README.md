![](https://github.com/ksh93/ksh/workflows/CI/badge.svg)

# KornShell 93u+m

This is version 1.0.x of the 93u+m fork of the KornShell, including a
sizeable number of enhancements and roughly a thousand bugfixes compared
to the last stable release (93u+ 2012-08-01) of
[ksh93](http://www.kornshell.com/),
formerly developed by AT&T Software Technology (AST).
The sources in this repository were forked from the
GitHub [AST repository](https://github.com/att/ast)
which is no longer under active development.

For information on the shell, see
[`src/cmd/ksh93/README`](https://github.com/ksh93/ksh/tree/1.0/src/cmd/ksh93#readme)
and other files in the same directory.
For user-visible fixes, see [NEWS](https://github.com/ksh93/ksh/blame/1.0/NEWS)
and click on commit messages for full details.
For all fixes, see [the commit log](https://github.com/ksh93/ksh/commits/1.0).
For known issues in the current release, see [TODO](https://github.com/ksh93/ksh/blob/1.0/TODO).

## Build

To build ksh with a custom configuration of features, edit
[`src/cmd/ksh93/SHOPT.sh`](https://github.com/ksh93/ksh/blob/1.0/src/cmd/ksh93/SHOPT.sh).

Then `cd` to the top directory and run:
```sh
bin/package make
```

The compiled binaries are stored in the `arch` directory, in a subdirectory
that corresponds to your architecture. The command `bin/package host type`
outputs the name of this subdirectory.

If you have trouble or want to tune the binaries, you may pass additional
compiler and linker flags. It is usually best to export these as environment
variables *before* running `bin/package` as they could change the name of
the build subdirectory of the `arch` directory, so exporting them is a
convenient way to keep them consistent between build and test commands.
**Note that this system uses `CCFLAGS` instead of the usual `CFLAGS`.**
An example that makes Solaris Studio cc produce a 64-bit binary:
```sh
export CCFLAGS="-m64 -O" LDFLAGS="-m64"
bin/package make
```
Alternatively you can append these to the command, and they will only be
used for that command. You can also specify an alternative shell in which
to run the build scripts this way. For example:
```sh
bin/package make SHELL=/bin/bash CCFLAGS="-O2 -I/opt/local/include" LDFLAGS="-L/opt/local/lib"
```

**Note:** Do not add compiler flags that cause the compiler to emit terminal
escape codes, such as `-fdiagnostics-color=always`; this will cause the
build to fail as the probing code greps compiler diagnostics.

For more information run
```sh
bin/package help
```
Many other commands in this repo self-document via the `--help`, `--man` and
`--html` options; those that do have no separate manual page.
The autoloadable `man` function in
[`src/cmd/ksh93/fun/man`](https://github.com/ksh93/ksh/blob/1.0/src/cmd/ksh93/fun/man)
integrates this self-documentation into your regular `man` command.

### Test

After compiling, you can run the regression tests.
To run the default test sets for ksh and the build system, use:
```sh
bin/package test
```
For ksh, use the `shtests` command directly to control the regression test runs.
Start by reading the information printed by:
```sh
bin/shtests --man
```

### Install

Usage: `bin/package install` *destination_directory* [ *command* ... ]

Any command from the `arch` directory can be installed. If no *command* is
specified, `ksh` and `shcomp` are assumed.

The *destination_directory* is created if it does not exist. Commands are
installed in its `bin` subdirectory and each command's manual page, if
available, is installed in `share/man`.

Destination directories with whitespace or shell pattern characters in their
pathnames are not yet supported.

## What is ksh93?

The following is the official AT&T description from 1993 that came with the
ast-open distribution. The text is original, but hyperlinks were added here.

----

KSH-93 is the most recent version of the KornShell Language described in
"The KornShell Command and Programming Language," by Morris Bolsky and David
Korn of AT&T Bell Laboratories, ISBN 0-13-182700-6. The KornShell is a shell
programming language, which is upward compatible with "sh" (the Bourne
Shell), and is intended to conform to the IEEE P1003.2/ISO 9945.2
[Shell and Utilities standard](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/contents.html).
KSH-93 provides an enhanced programming environment in addition to the major
command-entry features of the BSD shell "csh". With KSH-93, medium-sized
programming tasks can be performed at shell-level without a significant loss
in performance. In addition, "sh" scripts can be run on KSH-93 without
modification.

The code should conform to the
[IEEE POSIX 1003.1 standard](http://www.opengroup.org/austin/papers/posix_faq.html)
and to the proposed ANSI C standard so that it should be portable to all
such systems. Like the previous version, KSH-88, it is designed to accept
eight bit character sets transparently, thereby making it internationally
compatible. It can support multi-byte characters sets with some
characteristics of the character set given at run time.

KSH-93 provides the following features, many of which were also inherent in
KSH-88:

* Enhanced Command Re-entry Capability: The KSH-93 history function records
  commands entered at any shell level and stores them, up to a
  user-specified limit, even after you log off. This allows you to re-enter
  long commands with a few keystrokes - even those commands you entered
  yesterday. The history file allows for eight bit characters in commands
  and supports essentially unlimited size histories.
* In-line Editing: In "sh", the only way to fix mistyped commands is to
  backspace or retype the line. KSH-93 allows you to edit a command line
  using a choice of EMACS-TC or "vi" functions. You can use the in-line
  editors to complete filenames as you type them. You may also use this
  editing feature when entering command lines from your history file. A user
  can capture keystrokes and rebind keys to customize the editing interface.
* Extended I/O Capabilities: KSH-93 provides several I/O capabilities not
  available in "sh", including the ability to:
  * specify a file descriptor for input and output
  * start up and run co-processes
  * produce a prompt at the terminal before a read
  * easily format and interpret responses to a menu
  * echo lines exactly as output without escape processing
  * format output using printf formats.
  * read and echo lines ending in "\\". 
* Improved performance: KSH-93 executes many scripts faster than the System
  V Bourne shell. A major reason for this is that many of the standard
  utilities are built-in. To reduce the time to initiate a command, KSH-93
  allows commands to be added as built-ins at run time on systems that
  support dynamic loading such as System V Release 4.
* Arithmetic: KSH-93 allows you to do integer arithmetic in any base from
  two to sixty-four. You can also do double precision floating point
  arithmetic. Almost the complete set of C language operators are available
  with the same syntax and precedence. Arithmetic expressions can be used to
  as an argument expansion or as a separate command. In addition, there is an
  arithmetic for command that works like the for statement in C.
* Arrays: KSH-93 supports both indexed and associative arrays. The subscript
  for an indexed array is an arithmetic expression, whereas, the subscript
  for an associative array is a string.
* Shell Functions and Aliases: Two mechanisms - functions and aliases - can
  be used to assign a user-selected identifier to an existing command or
  shell script. Functions allow local variables and provide scoping for
  exception handling. Functions can be searched for and loaded on first
  reference the way scripts are.
* Substring Capabilities: KSH-93 allows you to create a substring of any
  given string either by specifying the starting offset and length, or by
  stripping off leading or trailing substrings during parameter
  substitution. You can also specify attributes, such as upper and lower
  case, field width, and justification to shell variables.
* More pattern matching capabilities: KSH-93 allows you to specify extended
  regular expressions for file and string matches.
* KSH-93 uses a hierarchical name space for variables. Compound variables can
  be defined and variables can be passed by reference. In addition, each
  variable can have one or more disciplines associated with it to intercept
  assignments and references.
* Improved debugging: KSH-93 can generate line numbers on execution traces.
  Also, I/O redirections are now traced. There is a DEBUG trap that gets
  evaluated before each command so that errors can be localized.
* Job Control: On systems that support job control, including System V
  Release 4, KSH-93 provides a job-control mechanism almost identical to
  that of the BSD "csh", version 4.1. This feature allows you to stop and
  restart programs, and to move programs between the foreground and the
  background.
* Added security: KSH-93 can execute scripts which do not have read
  permission and scripts which have the setuid and/or setgid set when
  invoked by name, rather than as an argument to the shell. It is possible
  to log or control the execution of setuid and/or setgid scripts. The
  noclobber option prevents you from accidentally erasing a file by
  redirecting to an existing file.
* KSH-93 can be extended by adding built-in commands at run time. In
  addition, KSH-93 can be used as a library that can be embedded into an
  application to allow scripting.

Documentation for KSH-93 consists of an "Introduction to KSH-93",
"Compatibility with the Bourne Shell" and a manual page and a README file.
In addition, the "New KornShell Command and Programming Language" book is
available from Prentice Hall.
