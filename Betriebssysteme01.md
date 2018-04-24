# Betriebssystem Praktikum 01

## Aufgabe 1

| Befehl | Paramter | Beschreibung                             |
| ------ | -------- | ---------------------------------------- |
| man    |          | Zeigt manpage des übergebenen Argumentes |
| pwd    |          | Gibt Name des aktuellen Arbeitsverzeichnis aus |
| ls     |          | Liste des Verzeichnisinhaltes            |
|        | -a       | Zeigt alle Inhalte an                    |
|        | -l       | Zeigt mehr Informationen an              |
|        | -al      | Kombination aus -a und -l                |
| cd     |          | Verzeichnis wechseln                     |
| mkdir  |          | Verzeichnis erstellen                    |
|        | -m       | Setzen der File-Mode                     |
|        | -v       | Gibt eine Nachricht für jedes erstellte Verzeichnis aus |
| rm     |          | Löschen einer Datei/Verzeichnis          |
|        | -f       | Force                                    |
|        | -d       | leeres Verzeichnis löschen               |
|        | -r       | rekursives löschen von Verzeichnissen    |
| cp     |          |                                          |
|        | -l       | Hard linken anstelle von Kopieren        |
|        | -r       | rekursives kopieren                      |
|        | -v       | Nur kopieren, wenn die Src neuer als die Dest ist |
| mv     |          | move                                     |
|        | -v       | Nur verschieben, wenn die Src neure als die Dest ist |
| more   |          | Gibt den Inhalt einer Datei aus          |
|        | -d       | Zeigt Steuerungsbefehl                   |
|        | -f       | logische Lines, nicht Screenlines        |
|        | -number  | Zu nutzende Screensize                   |
|        | +number  | Start bei angegebener Zeile              |
| tar    |          | Archivierungstool                        |
|        | -A       | Archiv an ein anderes Archiv hängen      |
|        | -c       | Neues Archiv erstellen                   |
|        | -d       | Unterschiede zwischen einen Archiv und Fliesystem suchen |
|        | --delete | Löschen des Angegeben Teil des Systems   |
|        | -t       | Inhalt anzeigen                          |
|        | -x       | extrahieren                              |
| top    |          | Zeigt Linux Prozesse an                  |
|        | -d       | Update Zeit bestimmen                    |
|        | -H       | Zeigt einzelne Threads                   |
|        | -p       | Zeigt nur Prozesse mit der übergebenen PID an |
| uname  |          | Anzeigen von Systeminformationen         |
|        | -a       | Alle Informationen                       |
|        | -s       | Kernel Name                              |
|        | -n       | Netzwerkname                             |
|        | -v       | Kernel Version                           |
|        | -p       | Prozessortyp                             |
|        | -o       | Betriebssystem                           |
| gzip   |          | Kompremierungstoole                      |
|        | -d       | dekompremieren                           |
|        | -r       | rekursiv                                 |

###Was macht der Befehl find . | xargs grep testString

- find . =Suche nach Datein im aktullen Verzeichnis
- | = übergibt Ausgabe vom Ersten Befehl an den Zweiten
- xargs = nächster Befehl wird für jede eingehnde Zeile ausgeführt
- grep testString =sucht in Datein nach 'testString'

Zusammengefasst: Der Befehl sucht in jeder Datei des aktuellen Verzeichnis nach den String 'testString'

## Aufgabe 2
```
mv ./Download/file.tar.gz ./unserBetriebssystemVerzeichnis
cd ./unserBetriebssystemVerzeichnis
tar -xfz ./file.tar.gz
ls | head -n 1
ls | head -n 1| xargs rm
```


### Metazeichen

Metazeichen wie *?*  oder \* sind normalerweise Platzhalter für ein oder mehrere Beliebige Zeichen. Wenn eine Datei/Verzeichnis ein Metazeichen im Namen hat, muss diesen mithilfe eines Backslashes Escaped werden. Metazeichen finden vorallem Anwendung in Regulären ausdrücken. 



## Aufgabe 3
```
tar -xfz ./dirStruct.tar.gz
rm -r ./rootTest
tar -xfz ./dirStruct.tar.gz
cd ./rootTest/dir1
```
###Befehl rm * .txt 

Der Befehl *rm * .txt* löscht alle Datein (*) und die Datei .txt im aktuellen Verzeichnis. Grund dafür ist das Leerzeichen zwischen * und .txt. Dieser Befehl kann nicht rückgängig gemacht werden.





