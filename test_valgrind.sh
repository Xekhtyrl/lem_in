#!/bin/bash

PROGRAM=./lem_in
ROOT_DIR=error_maps

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

TOTAL=0
FAILED=0

echo "===== VALGRIND TESTS ====="
echo ""

# Parcours tous les fichiers dans tous les sous-dossiers
find "$ROOT_DIR" -type f | while read -r file
do
    TOTAL=$((TOTAL+1))

    echo -n "Testing $file ... "

    valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --errors-for-leak-kinds=all \
        --error-exitcode=42 \
        $PROGRAM < "$file" >> ./log.txt 2>&1

    # Vérifie si la commande précédente s'est exécutée avec succès (code de sortie 0)
    if [ $? -eq 0 ]
    then
        echo -e "${GREEN}OK${NC}"
    else
        echo -e "${RED}FAIL${NC}"
        FAILED=$((FAILED+1))
    fi
done

echo ""
echo "Tests finished."