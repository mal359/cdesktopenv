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
: convert command that operates on file args to pipeline filter

(command set -o posix) 2>/dev/null && set -o posix

command=filter

TMPDIR=${TMPDIR:-/tmp}
export TMPDIR
tmp=$TMPDIR/$command$$
suf=

case `(getopts '[-][123:xyz]' opt --xyz; echo 0$opt) 2>/dev/null` in
0123)	ARGV0="-a $command"
	USAGE=$'
[-?
@(#)$Id: filter (AT&T Labs Research) 2001-05-31 $
]
[-author?Glenn Fowler <gsf@research.att.com>]
[-copyright?Copyright (c) 1994-2012 AT&T Intellectual Property]
[-license?https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html]
[+NAME?filter - run a command in stdin/stdout mode]
[+DESCRIPTION?\bfilter\b runs \acommand\a in a mode that takes input from
	the \afile\a operands, or from the standard input if no \afile\a
	operands are specified, and writes the results to the standard output.
	It can be used to run commands like \bsplit\b(1), that normally modify
	\afile\a operands in-place, in pipelines. The \afile\a operands are
	not modified; \acommand\a is run on copies in \b/tmp\b.]

command [ option ... ] [ file ... ]

[+SEE ALSO?\bstrip\b(1)]
'
	;;
*)	ARGV0=""
	USAGE="command [ option ... ] [ file ... ]"
	;;
esac

usage()
{
	OPTIND=0
	getopts $ARGV0 "$USAGE" OPT '-?'
	exit 2
}

while	getopts $ARGV0 "$USAGE" OPT
do	case $OPT in
	*)	usage ;;
	esac
done
shift `expr $OPTIND - 1`
case $# in
0)	usage ;;
esac

cmd=$1
while	:
do	shift
	case $# in
	0)	break ;;
	esac
	case $1 in
	-*)	cmd="$cmd $1" ;;
	*)	break ;;
	esac
done
trap 'rm -f $tmp$suf' 0 1 2 3 15
case $# in
0)	cat > $tmp
	$cmd $tmp
	;;
*)	for file
	do	suf=${file##*/}
		case $suf in
		*.*)	suf=.${suf#*.} ;;
		*)	suf= ;;
		esac
		cp $file $tmp$suf || exit 1
		chmod u+rwx $tmp$suf || exit 1
		$cmd $tmp$suf || exit 1
		cat $tmp$suf
		rm -f $tmp$suf
	done
	;;
esac
