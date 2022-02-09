# CommunicationEntre2uC

Ce projet consiste à établir une connexion ou une ocmmunication entre deux microcontrôleurs à partir du protocole I2C. J'ai choisi le ESP32 DOIT V1 DEVKIT et le MKR WIFI 1010.

L'idée du projet consiste à utiliser comme pour le control du Servo Moteur, utilser un uC pour envoyer les données de contrôl de l'angle, utiliser un autre uC
pour faire varier le Servo Moteur suivant les valeurs envoyées à partir du 1er uC.

Pour mieux perfectionner le projet, utiliser aussi un afficheur LCD (soit l'afficheur OLED, ou l'afficheur LCD de DFRobot 16x2) qui communique suivant le protocole I2C.
