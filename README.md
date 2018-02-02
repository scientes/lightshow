
Projekt: Lightshow

#Hinweise:

- Musik direkt im Program funktioniert zuzreit nur in Linux und die quelle is nur über das Makro in effect.h definierbar.
- Das Prgramm selbst wurde bis jetzt nur Auf Debian Linux und OSX getestet. Es kann sein das es auf nicht Unix Systemen (z.B Windows) nicht funktioniert
- Falls jemand es auf Windows testet bitte Feedback geben und/oder selbst so anpassen das es auf allen Systemen funktioniert.

# Spezifikation

Die Idee unseres Projektes ist es ein Programm zu schreiben, welches in der Lage ist in einem Fenster animierte Formen zu zeichnen. Diese Bildinformationen sollen später verwendet werden, um sie über einen Beamer darzustellen und mithilfe einer Nebelmaschine räumliche Effekte ähnlich derer einer professionellen Laser-show zu erzeugen. Dies soll so funktionieren, dass das vom Beamer erzeugte Licht am Nebel gestreut wird, sodass ein Volumetrischer Effekt entsteht. 


# Leistungsmerkmale

Damit das Programm grundlegend funktioniert, muss es in der Lage sein ein Fenster mit dynamischem Inhalt zu erzeugen, in welchem schließlich die Formen gezeichnet werden. Es ist zunächst also notwendig, dass das Programm in der Lage ist ein Fenster mit schwarzem Inhalt zu erstellen (1), welches dann in der Anwendung einen leeren Lichteffekt repräsentiert. Aufgrund der In herkömmlichen Beamern verwendeten Technik kommt es jedoch auch bei einem schwarzem Bild zur aussendung von Licht, welches vermutlich für sichtbare Störeffekte verursachen wird. Für unsere Anwendung sollte dies allerdings nicht kritisch sein, da dieses Licht vermutlich eine geringe Intensität hat und sich das störende Licht somit in Grenzen hält. 
Um Mithilfe des Aufbaus einen räumlichen Strahl zu erzeugen, muss auf der Schwarzen Projektionsfläche vom Programm ein Punkt gezeichnet werden können (2). Der Strahl (sowie auch andere Lichteffekte) sollten auch in unterschiedliche Farben annehmen können, um mehr Abwechslung in der Lichtshow zu erzeugen. (3) Es sollte zudem möglich sein, die Strahlen ein und ausblenden zu lassen, sowie mehrere Strahlen gleichzeitig zu erzeugen. Am besten auch durch Nutzereingaben. (4) Neben einfachen Strahlen sollte es auch möglich sein andere einfache Formen zu erstellen, wie Ebenen oder Wellen. (5) Damit die Lichtshow lebendiger ist sollten sich diese Formen ebenfalls über die Projektionsfläche bewegen können sowie schnelle Richtungswechsel und ähnliches vollziehen können. (6) Um die Lichteffekte passend mit dem Takt (extern) gespielter Musik zu synchronisieren sollte es einen Modus geben, in welchem der Nutzer Mithilfe zeitlich abgestimmter Eingaben in der Lage ist, beispielsweise die Bewegungsrichtung des Effekts, die Farbe, oder andere Parameter des aktuell gespielten Effekts zu ändern. (7) 

# Design

Für die technische Umsetzung der Projektidee ist es notwendig eine Graphikbibliothek zu verwenden, die in C funktioniert. Unser Ansatz ist, hierfür SDL 2.0 zu verwenden, welches eine kostenlose Open-Source Anwendung ist. Für die grundsätzliche Umsetzung ist also der wichtigste Schritt diese Graphikbibliothek auf den entsprechenden Computern zu installieren und in einem C Code funktionierend zu inkludieren. Zudem müssen die von der Bibliothek bereitgestellten Funktionen zum erstellen eines Fensters mit bestimmten Maßen, sowie zum verändern des Inhaltes des Fensters bekannt sein. Solche Funktionen zum verändern des Inhaltes müssen in der Lage sein, die von uns angestrebten Formen bei festgelegten Koordinaten in der Zeichenfläche zu zeichnen. 






# Struktur des Programms

Unser Programm soll aus mehreren Dateien bestehen (aus übersichtlichkeits Gründen), wichtige Funktionen sollen in .h Dateien ausgelagert werden. Wir streben an beispielsweise drei .h Dateien zu haben: 
1.	renderer.h (kommunikation mit der Graphikkarte über SDL)
2.	effect.h (Die eigentlichen Effekte)
3.	music.h (managed das Abspielen der Musik)
In dem Hauptcode (lightshow.c) befindet sich die main. Hier alle Inputs (einschließlich Nutzereingaben) gemanaged werden. Am Anfang des Codes müssen zunächst alle notwendigen Bibliotheken inkludiert werden. Anschließend muss in der main mithilfe einer Funktion von SDL ein Fenster mit Schwarzem Inhalt erstellt werden, welches im Vollbild angezeigt wird. Dann folgt der main Loop, der jedes Frame einzeln gerneriert. In diesem werden die Effekte abhängig vom Input in das Fenster gezeichnet. Am Anfang des main loop wir der (User-) Input abgefragt, dieser wird als Int- wert / Array an eine Funktion aus der renderer.h übergeben. In dieser wird mithilfe einer Switch Anweisung zwischen den unterschiedlichen Effekten unterschieden. Die renderer.h zeichnet mithilfe der Funktionen, welcher in der effect.h Datei ausgelagert sind anschießend die die Effekte auf die Projektionsfläche zeichnet. 

# Variablen

##Zentrale Datentypen
-	Für den main Loop, muss es eine Abbruchvariable (Int) geben, welche das Programm jederzeit beenden kann. 
-	Int Variable, die die Anfangszeit des Programms speichert
-	Int Variable/ Array, welche die Effektauswahl/en speichert
-	Int Fps Zahl 
-	Variablen mit der Bildschirmgröße (width, height)

## Lokale Datentypen
-	Int Positionsvariablen (X, Y, x, y)
-	


# Funktionen
-	Effektfunktionen (Int Zeit, (Int Koordinaten), Renderer/ Fenster (SDL Variable))
o	Return: 0
-	(Viele SDL Funktionen)










/*
 Das gesamte restliche Programm steht in einen main Loop (also in einer Endlosschleife). Hierfür sollte es eine Int- Variable „running“ geben, welche in einer while-Schleife Abgefragt wird (running = 1 -> Programm läuft; running = 0 -> Programm wird beendet). 





Anschließend kommt (eventuell nach einer graphischen Ausgabe) eine scanf Funktion, in welcher der User durch seinen Input einen der Programmmodi des Programmes wählen kann. Hierzu ist eine Int- Variable „mode“ notwendig. Dann kommt ein Switch, welcher in den richtigen Modus schaltet. In den entsprechenden Cases des Switch steht nun der Code, welcher den Inhalt des Fensters verändert, indem beispielsweise Formen gezeichnet werden. In case 1 steht nun der Code, um Leistungsmerkmal (2) zu verwirklichen. 
*/
