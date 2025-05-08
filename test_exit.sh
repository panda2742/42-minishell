#!/bin/bash

make > /dev/null

script -q -c "./minishell -t 2" /dev/null <<EOF | tail -n+3 > out_a
$*
EOF

script -q -c "bash --posix" /dev/null <<EOF | tail -n+3 > out_b
$*
EOF

echo "--- Minishell: "
cat out_a
echo -e "\n--- Bash posix (interactive): "
cat out_b

echo -e "\n--- Diff: "
diff -u out_a out_b

rm out_a out_b