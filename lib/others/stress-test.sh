P=code   # código a testar
Q=brute  # brute correto
C=       # checker; vazio usa cmp

g++ "$P.cpp" -o sol -O2 || exit 1
g++ "$Q.cpp" -o brt -O2 || exit 1
g++ gen.cpp -o gen -O2 || exit 1
if [ -n "$C" ]; then
  g++ "$C.cpp" -o chk -O2 || exit 1
fi

for ((i = 1; ; i++)); do
  echo "$i"
  ./gen "$i" > in
  ./sol < in > out
  ./brt < in > out2
  if [ -n "$C" ]; then
    ./chk in out out2
  else
    cmp -s out out2
  fi
  if [ $? -ne 0 ]; then
    echo "--> entrada:"
    cat in
    echo "--> saída code:"
    cat out
    echo "--> saída brute:"
    cat out2
    break
  fi
done
