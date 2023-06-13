-- Drop

DROP SCHEMA IF EXISTS transmusicales CASCADE ;
CREATE SCHEMA transmusicales;
SET SCHEMA 'transmusicales';

-- Les tables

CREATE TABLE Type_musique (
   type_m VARCHAR(30) PRIMARY KEY
);


CREATE TABLE Concert (
   no_concert VARCHAR(2) PRIMARY KEY,
   titre VARCHAR(30),
   resume CHAR,
   duree INT,
   tarif FLOAT,
   nom_edition VARCHAR(20),
   type_m VARCHAR(20)
);


CREATE TABLE Representation (
   numero_representation VARCHAR(2) PRIMARY KEY NOT NULL,
   heure VARCHAR(6),
   date_representation DATE,
   id_Groupe_Artiste VARCHAR(3) NOT NULL,
   id_lieu VARCHAR(3) NOT NULL,
   no_concert VARCHAR(5) NOT NULL
);


CREATE TABLE Formation (
   libelle_formation VARCHAR(50) PRIMARY KEY
);


CREATE TABLE Lieu (
   id_lieu VARCHAR(2) PRIMARY KEY,
   nom_lieu VARCHAR(30),
   accesPMR BOOL,
   capacite_max INT,
   type_lieu CHAR,
   nom_v VARCHAR(20)
);


CREATE TABLE Ville (
   nom_v VARCHAR(30) PRIMARY KEY NOT NULL,
   nom_p VARCHAR(30)
);


CREATE TABLE Pays (
   nom_p VARCHAR(30) PRIMARY KEY NOT NULL
);


CREATE TABLE Edition (
   nom_edition VARCHAR(50) PRIMARY KEY NOT NULL,
   annee_edition INT NOT NULL
);


CREATE TABLE Annee (
   an INT PRIMARY KEY NOT NULL
);


CREATE TABLE Groupe_artiste (
   id_Groupe_Artiste VARCHAR(2) PRIMARY KEY,
   nom_groupe_artiste VARCHAR(50),
   annee_debut INT NOT NULL,
   site_web VARCHAR(20),
   pays_origine VARCHAR(30) NOT NULL,
   an_discographique INT NOT NULL,
   libelle_formation VARCHAR(50) NOT NULL,
   type_ponctuel_m VARCHAR(20) NOT NULL,
   type_principal_m VARCHAR(20) NOT NULL
);


-- Les Relations entre les tables


ALTER TABLE Groupe_artiste
ADD CONSTRAINT fk_ga_annee
FOREIGN KEY (annee_debut) REFERENCES Annee(an);


ALTER TABLE Groupe_artiste
ADD CONSTRAINT fk_ga_disco
FOREIGN KEY (an_discographique) REFERENCES Annee(an);


ALTER TABLE Groupe_artiste
ADD CONSTRAINT fk_ga_pays
FOREIGN KEY (pays_origine) REFERENCES Pays(nom_p);


ALTER TABLE Groupe_artiste
ADD CONSTRAINT fk_ga_formation
FOREIGN KEY (libelle_formation) REFERENCES Formation(libelle_formation);


ALTER TABLE Groupe_artiste
ADD CONSTRAINT fk_ga_poncutel
FOREIGN KEY (type_ponctuel_m) REFERENCES Type_musique(type_m);


ALTER TABLE Groupe_artiste
ADD CONSTRAINT fk_ga_principal
FOREIGN KEY (type_principal_m) REFERENCES Type_musique(type_m);


ALTER TABLE Ville
ADD CONSTRAINT fk_ville_lieu
FOREIGN KEY (nom_p) REFERENCES Pays(nom_p);


ALTER TABLE Edition
ADD CONSTRAINT fk_edition_annee
FOREIGN KEY (annee_edition) REFERENCES annee(an);


ALTER TABLE Lieu
ADD CONSTRAINT fk_lieu_ville
FOREIGN KEY (nom_v) REFERENCES Ville(nom_v);


ALTER TABLE Concert
ADD CONSTRAINT fk_concert_edition
FOREIGN KEY (nom_edition) REFERENCES Edition(nom_edition);


ALTER TABLE Concert
ADD CONSTRAINT fk_concert_type_musique
FOREIGN KEY (type_m) REFERENCES Type_musique(type_m);


ALTER TABLE Representation
ADD CONSTRAINT fk_lieu FOREIGN KEY (id_lieu) REFERENCES Lieu(id_lieu);


ALTER TABLE Representation
ADD CONSTRAINT fk_noconcert FOREIGN KEY (no_concert) REFERENCES Concert(no_concert);


ALTER TABLE Representation
ADD CONSTRAINT fk_typem FOREIGN KEY (id_Groupe_Artiste) REFERENCES Groupe_artiste(id_Groupe_Artiste);

