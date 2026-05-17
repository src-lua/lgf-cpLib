	P=code   #codigo a testar
	Q=brute  #brute correto
	C=		 #checker (vazio=cmp, ou ex: C=checker)
	g++ ${P}.cpp -o sol -O2 || exit 1
	g++ ${Q}.cpp -o brt -O2 || exit 1
	g++ gen.cpp  -o gen -O2 || exit 1
	[ -n "$C" ] && { g++ ${C}.cpp -o chk -O2 || exit 1; }
	for ((i = 1; ; i++)) do
		echo $i
		./gen $i > in
		./sol < in > out
		./brt < in > out2
		[ -n "$C" ] && ./chk in out out2 || cmp -s out out2
		if [ $? -ne 0 ]; then
			echo "--> entrada:"
			cat in
			echo "--> saida code:"
			cat out
			echo "--> saida brute:"
			cat out2
			break
		fi
	done