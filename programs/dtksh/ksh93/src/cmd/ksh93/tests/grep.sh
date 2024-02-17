########################################################################
#                                                                      #
#               This software is part of the ast package               #
#          Copyright (c) 1982-2011 AT&T Intellectual Property          #
#          Copyright (c) 2020-2022 Contributors to ksh 93u+m           #
#                      and is licensed under the                       #
#                 Eclipse Public License, Version 2.0                  #
#                                                                      #
#                A copy of the License is available at                 #
#      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      #
#         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         #
#                                                                      #
#                  David Korn <dgk@research.att.com>                   #
#                  Martijn Dekker <martijn@inlv.org>                   #
#            Johnothan King <johnothanking@protonmail.com>             #
#                                                                      #
########################################################################

. "${SHTESTS_COMMON:-${0%/*}/_common}"

function grep
{
	#
	#	SHELL VERSION OF GREP
	#
	vflag= xflag= cflag= lflag= nflag=
	set -f
	while	((1))				# look for grep options
	do	case	"$1" in
		-v*)	vflag=1;;
		-x*)	xflag=1;;
		-c*)	cflag=1;;
		-l*)	lflag=1;;
		-n*)	nflag=1;;
		-b*)	print 'b option not supported';;
		-e*)	shift;expr="$1";;
		-f*)	shift;expr=$(< $1);;
		-*)	print $0: 'unknown flag';return 2;;
		*)
			if	test "$expr" = ''
			then	expr="$1";shift
			fi
			test "$xflag" || expr="*${expr}*"
			break;;
		esac
		shift				# next argument
	done
	noprint=$vflag$cflag$lflag		# don't print if these flags are set
	integer n=0 c=0 tc=0 nargs=$#		# initialize counters
	for i in "$@"				# go through the files
	do	if	((nargs<=1))
		then	fname=''
		else	fname="$i":
		fi
		test "$i"  &&  exec 0< $i	# open file if necessary
		while	read -r line		# read in a line
		do	let n=n+1
			case	"$line" in
			$expr)			# line matches pattern
				test "$noprint" || print -r -- "$fname${nflag:+$n:}$line"
				let c=c+1 ;;
			*)			# not a match
				if	test "$vflag"
				then	print -r -- "$fname${nflag:+$n:}$line"
				fi;;
			esac
		done
		if	test "$lflag" && ((c))
		then	print -r -- "$i"
		fi
		let tc=tc+c n=0 c=0
	done
	test "$cflag" && print $tc		#  print count if cflag is set
	let tc					#  set the return value
}

cat > $tmp/grep <<\!
this is a food bar test
to see how many lines find both foo and bar.
Some line contain foo only,
and some lines contain bar only.
However, many lines contain both foo and also bar.
A line containing foobar should also be counted.
There should be six lines with foo and bar.
There are only two lines without foo but with bar.
!

got=$(grep -c 'foo*bar' $tmp/grep 2>&1)
if	[[ $got != 6 ]]
then	err_exit "shell version of grep fails (expected 6, got $(printf %q "$got"))"
fi

exit $((Errors<125?Errors:125))
