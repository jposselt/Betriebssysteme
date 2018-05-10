#!/bin/bash

# Shell Script zum Wiederherlstellen von Dateien aus dem Papierkorb

TRASHDIR="$HOME/.trashBin"
TRASHLOG="$TRASHDIR/.dir"

# Parameter prüfen
if [ -z "$1" ]
then
    echo "Usage: $0 [FILE]..."
    exit 1
fi

# Papierkorb existiert?
if [ ! -e "$TRASHDIR" ]
then
    echo "Papierkorbverzeichnis nicht gefunden"
    exit 1
fi

# Logdatei existiert?
if [ ! -e "$TRASHLOG" ]
then
    echo "Papierkorb-Logdatei nicht gefunden"
    exit 1
fi

# Iteration über Parameterliste
for FILE in "$@"
do
    # Zeile in Logdatei finden
    LINE=$(grep ^"$FILE"! "$TRASHLOG")

    if [ $? ]
    then
	# Ursprungspfad holen und prüfen
	# Befehl basename
	echo $LINE
	# Datei wiederherstellen

	# Zeile aus Logdatei entfernen
	# sed- i ...
    else
	echo "$FILE nicht gefunden"
    fi
    
done
