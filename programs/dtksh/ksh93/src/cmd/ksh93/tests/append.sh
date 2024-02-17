########################################################################
#                                                                      #
#               This software is part of the ast package               #
#          Copyright (c) 1982-2012 AT&T Intellectual Property          #
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
#                                                                      #
########################################################################

. "${SHTESTS_COMMON:-${0%/*}/_common}"

{
x=abc
x+=def ;} 2> /dev/null
if	[[ $x != abcdef ]]
then	err_exit 'abc+def != abcdef'
fi
integer i=3
{ i+=4;} 2> /dev/null
if	(( i != 7 ))
then	err_exit '3+4!=7'
fi
iarray=( one two three )
{ iarray+= (four five six) ;} 2> /dev/null
if	[[ ${iarray[@]} != 'one two three four five six' ]]
then	err_exit 'indexed array append fails'
fi
unset iarray
iarray=one
{ iarray+= (four five six) ;} 2> /dev/null
if	[[ ${iarray[@]} != 'one four five six' ]]
then	err_exit 'indexed array append to scalar fails'
fi
typeset -A aarray
aarray=( [1]=1 [3]=4 [xyz]=xyz )
aarray+=( [2]=2 [3]=3 [foo]=bar )
if	[[ ${aarray[3]} != 3 ]]
then	err_exit 'associative array append fails'
fi
if	[[ ${#aarray[@]} != 5 ]]
then	err_exit 'number of elements of associative array append fails'
fi
point=(x=1 y=2)
point+=( y=3 z=4)
if	[[ ${point.y} != 3 ]]
then	err_exit 'compound append fails'
fi
if	[[ ${point.x} != 1 ]]
then	err_exit 'compound append to compound variable unsets existing variables'
fi
unset foo
foo=one
foo+=(two)
if	[[ ${foo[@]} != 'one two' ]]
then	err_exit 'array append to non array variable fails'
fi
unset foo
foo[0]=(x=3)
foo+=(x=4)
[[ ${foo[1].x} == 4 ]] || err_exit 'compound append to indexed array not working'
[[ ${foo[0].x} == 3 ]] || err_exit 'compound append to indexed array unsets existing variables'

unset foo
foo=a
foo+=''
[[ $foo == 'a' ]] || err_exit 'appending an empty string not working'

unset x z arr
typeset -a x=(a b)
x+=(c d)
exp='typeset -a x=(a b c d)'
[[ $(typeset -p x) == "$exp" ]] || err_exit 'append (c d) to indexed array not working'

typeset -a arr=(a=b b=c)
arr+=(c=d d=e)
exp='typeset -a arr=(a\=b b\=c c\=d d\=e)'
[[ $(typeset -p arr) == "$exp" ]] || err_exit 'append (c=d d=e) to indexed array not working'

exp='typeset -a z=(a\=b b\=c d\=3 e f\=l)'
typeset -a z=(a=b b=c)
{ z+=(d=3 e f=l); } 2> /dev/null
[[ $(typeset -p z) == "$exp" ]] || err_exit 'append (d=3 e f=l) to indexed array not working'

unset arr2
exp='typeset -a arr2=(b\=c :)'
typeset -a arr2
arr2+=(b=c :)
[[ $(typeset -p arr2) == "$exp" ]] || err_exit 'append (b=c :) to indexed array not working'

unset arr2
exp='typeset -a arr2=(b\=c xxxxx)'
typeset -a arr2
{
	arr2+=(b=c xxxxx)
} 2> /dev/null
[[ $(typeset -p arr2) == "$exp" ]] || err_exit 'append (b=c xxxxx) to indexed array not working'

exit $((Errors<125?Errors:125))
