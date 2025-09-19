📌 Description

Ce projet propose une implémentation bare metal du protocole I2C sur microcontrôleur STM32F4 sans utilisation de HAL ni de librairies externes.

L’objectif est de comprendre et maîtriser les registres bas-niveau permettant la communication I2C, et de fournir une base simple et pédagogique pour développer des applications embarquées.

⚡ Fonctionnalités

*Initialisation du périphérique I2C (mode maître).

*Génération des signaux Start et Stop.

*Envoi et réception de données octet par octet.

*Gestion des ACK/NACK.

*Exemple de communication avec un périphérique esclave.

🛠️ Matériel utilisé

*Microcontrôleur : STM32F4 (testé sur STM32F4xx, adaptable sur d’autres séries).

*Outil de développement : STM32CubeIDE / Makefile bare metal.

*Interface I2C sur broches standard (SCL, SDA).
