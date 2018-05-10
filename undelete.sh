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
	# Ursprungspfad holen
	SRCPATH="$(echo $LINE | cut -d'!' -f2)"	
	
	# Datei wiederherstellen
	if mv $TRASHDIR/$FILE $SRCPATH
	then	
		echo "Platzhalter"
		# Zeile aus Logdatei entfernen
		
	else 
		echo "Fehler beim wiederherstellen. Ursprungspfad nicht vorhaden"
	fi
	
    else
	echo "$FILE nicht gefunden"
    fi
    
done
