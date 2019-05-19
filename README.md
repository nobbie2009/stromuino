# stromuino
[Arduino] - Zeitgesteuerte Steckdosen

Dies ist mein erstes Projekt.
Es handelt sich hier um ein Projektfile für die IDE von Arduinio.

Benötigte Komponenten:
- Arduino (nano)
- Keypad-Shield
- (4er) Relaiskarte
- I2C LCD Shield

Nachdem der Arduino gestartet wurde kann man mittels der Sternchen-Taste die Auswahl des Relais anstoßen.
(Eingabe 1-4) danach wird die Zeit in Stunden und Minuten angegeben. Mit einem weiteren Druck auf die Raute-Taste 
wird der Countdown gestartet und das Relais geschalten.
Nach Ablauf des Countdowns oder nach Druck auf die Taste "D" wird das Relais erneut geschalten.
Wobei bei einem Druck auf die Taste "D" alle angeschlossenen Relais geschalten werden.

Dieses Projekt habe ich primär für mich privat erstellt, mit dem Hintergedanken, dass ich es in der Werkstatt nutzen möchte, 
in dieser habe ich diverse Ladegeräte stehen, mit denen ich die dazugehörigen Akkus nicht brutzeln möchte.
Daher sollte eine automatische Lösung her.
