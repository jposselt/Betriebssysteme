#!/bin/bash

# Shell Script zum 'löschen' von Dateien. Dateien werden zunächst in ein
# Papierkorbverzeichnis verschoben und nach Zeitstempel und PID benannt.

TRASHDIR="$HOME/.trashBin"
TRASHLOG="$TRASHDIR/.dir"

#echo $(date '+%y%m%d%H%M%S')

# Parameter prüfen
if [ -z "$1" ]
then
    echo "Usage: $0 [FILE]..."
    exit 1
fi

# Erzeuge Papierkorb, falls nicht vorhanden
if [ ! -e "$TRASHDIR" ]
then
    mkdir "$TRASHDIR"
fi

# Erzeuge Log-Datei, falls nicht vorhanden
if [ ! -e "$TRASHLOG" ]
then
    touch "$TRASHLOG"
fi

# Iteration über Parameterliste
for FILE in "$@"
do
    if [ -e "$FILE" ]
    then
	# Dateihandle anlegen
	HANDLE=$(date '+%y%m%d%H%M%S')_$$.dat

	# Datei verschieben (Copy zum Testen)
	cp "$FILE" "$TRASHDIR/$HANDLE"

	# Eintrag zur Logdatei hinzufügen
	echo $HANDLE! $(realpath -s "$FILE") >> "$TRASHLOG"

	# Ausgabe für Benutzer
	echo "$(realpath -s $FILE): $HANDLE"
    else
	echo "$FILE existiert nicht"
    fi
done


