########################################################################
#                                                                      #
#               This software is part of the ast package               #
#          Copyright (c) 1994-2011 AT&T Intellectual Property          #
#          Copyright (c) 2020-2022 Contributors to ksh 93u+m           #
#                      and is licensed under the                       #
#                 Eclipse Public License, Version 2.0                  #
#                                                                      #
#                A copy of the License is available at                 #
#      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      #
#         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         #
#                                                                      #
#                 Glenn Fowler <gsf@research.att.com>                  #
#                  Martijn Dekker <martijn@inlv.org>                   #
#                                                                      #
########################################################################
: wrapper for .exe challenged Win32 systems/commands

(command set -o posix) 2>/dev/null && set -o posix

command=execrate

bins=`
	(
		userPATH=$PATH
		PATH=/run/current-system/sw/bin:/usr/xpg7/bin:/usr/xpg6/bin:/usr/xpg4/bin:/bin:/usr/bin:$PATH
		getconf PATH 2>/dev/null && echo "$userPATH" || echo /bin:/usr/bin:/sbin:/usr/sbin:"$userPATH"
	) | sed 's/:/ /g'
` || exit

case `(getopts '[-][123:xyz]' opt --xyz; echo 0$opt) 2>/dev/null` in
0123)	ARGV0="-a $command"
	USAGE=$'
[-?
@(#)$Id: execrate (AT&T Labs Research) 2002-02-02 $
]
[-author?Glenn Fowler <gsf@research.att.com>]
[-copyright?Copyright (c) 2002-2012 AT&T Intellectual Property]
[-license?https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html]
[+NAME?execrate - wrapper for .exe challenged commands]
[+DESCRIPTION?\bexecrate\b runs \acommand\a after checking the \afile\a
	operands for standard semantics with respect to \bWin32\b \b.exe\b
	suffix conventions. This command is only needed on \bWin32\b
	systems that inconsistently handle \b.exe\b across library and
	command interfaces. \acommand\a may be one of \bcat\b(1), \bchmod\b(1),
	\bcmp\b(1), \bcp\b(1), \bln\b(1), \bmv\b(1), or \brm\b(1).
	Only the 2 argument forms of \bcp\b, \bln\b and \bmv\b are handled.
	Unsupported commands and commands requiring no change are
	silently executed.]
[+?With no arguments \bexecrate\b exits with status 0 if the current system
	is \b.exe\b challenged, 1 if the current system is normal.]
[n:show?Show the underlying commands but do not execute.]

command [ option ... ] file ...

[+SEE ALSO?\bwebster\b(1)]
'
	usage()
	{
		OPTIND=0
		getopts $ARGV0 "$USAGE" OPT '-?'
		exit 2
	}
	exec=1
	while	getopts $ARGV0 "$USAGE" OPT
	do	case $OPT in
		n)	exec=0 ;;
		*)	usage ;;
		esac
	done
	shift `expr $OPTIND - 1`
	;;
*)	usage()
	{
		echo "Usage: execrate [ -n ] [ command [ option ... ] file ... ]" >&2
		exit 2
	}
	exec=1
	while	:
	do	case $1 in
		-n)	exec=0 ;;
		-*)	usage ;;
		*)	break ;;
		esac
		shift
	done
	;;
esac
case $# in
0)	if	test ! -x /bin/cat.exe
	then	exit 1 # normal
	fi
	if	/bin/cat /bin/cat >/dev/null 2>&1
	then	exit 1 # normal
	fi
	exit 0 # challenged
	;;
1)	usage
	;;
esac
case $1 in
*cat|*rm)
	NUM=0
	;;
*chgrp|*chmod)
	NUM=1
	;;
*cmp|*cp|*ln|*mv)
	NUM=2
	;;
*)	case $exec in
	0)	echo "$@" ;;
	*)	"$@" ;;
	esac
	exit
	;;
esac
CMD=$1
shift
case $CMD in
*/*)	;;
*)	for d in $bins
	do	if	test -x $d/$1 -o -x $d/$1.exe
		then	CMD=$d/$1
			break
		fi
	done
	;;
esac
while	:
do	case $1 in
	-*)	CMD="$CMD $1" ;;
	*)	break ;;
	esac
	shift
done
case $exec in
0)	CMD="echo $CMD" ;;
esac
case $NUM:$# in
*:0)	;;
1:*)	CMD="$CMD $1"
	NUM=0
	shift
	;;
esac
case $NUM:$# in
0:*)	status=0
	for f
	do	if	test "$f" -ef "$f".exe
		then	f=$f.exe
		fi
		$CMD "$f"
		case $? in
		0)	;;
		*)	status=$? ;;
		esac
	done
	exit $status
	;;
2:2)	f=$1
	case $f in
	*.exe)	;;
	*)	if	test "$f" -ef "$f".exe
		then	f=$f.exe
		fi
		;;
	esac
	case $f in
	*.exe)	if	test -d "$2"
		then	t=$2/$f
		else	t=$2
		fi
		case $t in
		*/*)	b=`basename "$t"` ;;
		*)	b=$t ;;
		esac
		case $b in
		*.*)	$CMD "$f" "$t"; exit ;;
		*)	$CMD "$f" "$t".exe; exit ;;
		esac
		;;
	esac
	;;
esac
$CMD "$@"
