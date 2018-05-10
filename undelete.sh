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
	
    if [ "$?" -eq "0" ]
    then
	# Ursprungspfad holen
	SRCPATH=$(sed -n -e "s/^""$FILE""! //p" $TRASHLOG)
	
	# Datei wiederherstellen 	for silent mv
	mv "$TRASHDIR/$FILE" "$SRCPATH" 2>/dev/null
	if [ "$?" -eq "0" ]
	then	
		# Zeile aus Logdatei entfernen
		grep -v  "$FILE" "$TRASHLOG" > tempdatei
		mv tempdatei "$TRASHLOG"
		
	else 
		echo "Fehler beim wiederherstellen."
	fi
	
    else
	echo "Datei nicht vorhanden"
    fi
    
done
