DROP DATABASE IF EXISTS MLR3;

CREATE DATABASE  MLR3;
USE MLR3;
# -----------------------------------------------------------------------------
#       TABLE : ESPECES
# -----------------------------------------------------------------------------

CREATE TABLE  ESPECES
 (
   IDESPECE INTEGER(2) NOT NULL  ,
   IDREGIME INTEGER(2) NOT NULL  ,
   IDANIMAL INTEGER(2) NULL  ,
   NOMSCIE CHAR(127) NULL  ,
   NOMVULGE CHAR(63) NULL  ,
   NBINDIVIDUS INTEGER(2) NULL  ,
   MENACEE BOOL NULL  
   , PRIMARY KEY (IDESPECE) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE ESPECES
# -----------------------------------------------------------------------------


CREATE UNIQUE INDEX I_FK_ESPECES_REGIME
     ON ESPECES (IDREGIME ASC);

CREATE  INDEX I_FK_ESPECES_ANIMAUX
     ON ESPECES (IDANIMAL ASC);

# -----------------------------------------------------------------------------
#       TABLE : ENCLOS
# -----------------------------------------------------------------------------

CREATE TABLE  ENCLOS
 (
   IDENCLOS INTEGER(2) NOT NULL  ,
   CODEE CHAR(3) NULL  ,
   NOME CHAR(63) NULL  ,
   SURFACEE INTEGER(2) NULL  ,
   TYPEE CHAR(63) NULL  
   , PRIMARY KEY (IDENCLOS) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : ALIMENTS
# -----------------------------------------------------------------------------

CREATE TABLE  ALIMENTS
 (
   IDALIMENT INTEGER(2) NOT NULL  ,
   IDALIMENT_SUBSTITUT INTEGER(2) NULL  ,
   CODEA CHAR(3) NULL  ,
   DESIGNATIONA CHAR(63) NULL  ,
   STOCKA INTEGER(2) NULL  
   , PRIMARY KEY (IDALIMENT) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE ALIMENTS
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_ALIMENTS_ALIMENTS
     ON ALIMENTS (IDALIMENT_SUBSTITUT ASC);

# -----------------------------------------------------------------------------
#       TABLE : SOIGNEURS
# -----------------------------------------------------------------------------

CREATE TABLE  SOIGNEURS
 (
   IDSOIGNEUR INTEGER(2) NOT NULL  ,
   IDENCLOS INTEGER(2) NULL  ,
   NOMS CHAR(63) NULL  ,
   PRENOMS CHAR(63) NULL  ,
   DATES DATE NULL  
   , PRIMARY KEY (IDSOIGNEUR) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE SOIGNEURS
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_SOIGNEURS_ENCLOS
     ON SOIGNEURS (IDENCLOS ASC);

# -----------------------------------------------------------------------------
#       TABLE : FAMILLES
# -----------------------------------------------------------------------------

CREATE TABLE  FAMILLES
 (
   IDFAMILLE INTEGER(2) NOT NULL  ,
   NOMSCIF CHAR(127) NULL  
   , PRIMARY KEY (IDFAMILLE) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : ANIMAUX
# -----------------------------------------------------------------------------

CREATE TABLE  ANIMAUX
 (
   IDANIMAL INTEGER(2) NOT NULL  ,
   NOMA CHAR(63) NULL  ,
   SEXEA BOOLEAN NULL  ,
   DATENAISSANCE DATE NULL  ,
   DATEARRIVE DATE NULL  
   , PRIMARY KEY (IDANIMAL) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : REGIME
# -----------------------------------------------------------------------------

CREATE TABLE  REGIME
 (
   IDREGIME INTEGER(2) NOT NULL  ,
   SEXER BOOLEAN NULL  
   , PRIMARY KEY (IDREGIME) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : LOCALISATIONS
# -----------------------------------------------------------------------------

CREATE TABLE  LOCALISATIONS
 (
   IDLOCALISATION INTEGER(2) NOT NULL  ,
   CODEL CHAR(3) NULL  ,
   NOML CHAR(127) NULL  
   , PRIMARY KEY (IDLOCALISATION) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : APPARTENIRFAMILLE
# -----------------------------------------------------------------------------

CREATE TABLE  APPARTENIRFAMILLE
 (
   IDFAMILLE_1 INTEGER(2) NOT NULL  ,
   IDESPECE INTEGER(2) NOT NULL  ,
   IDFAMILLE INTEGER(2) NOT NULL  
   , PRIMARY KEY (IDFAMILLE_1) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE APPARTENIRFAMILLE
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_APPARTENIRFAMILLE_ESPECES
     ON APPARTENIRFAMILLE (IDESPECE ASC);

CREATE  INDEX I_FK_APPARTENIRFAMILLE_FAMILLES
     ON APPARTENIRFAMILLE (IDFAMILLE ASC);

# -----------------------------------------------------------------------------
#       TABLE : HISTORIQUEENCLOS
# -----------------------------------------------------------------------------

CREATE TABLE  HISTORIQUEENCLOS
 (
   IDENCLOS INTEGER(2) NOT NULL  ,
   IDANIMAL INTEGER(2) NOT NULL  ,
   DATEENTREE DATE NOT NULL  ,
   DATESORTIE DATE NULL  
   , PRIMARY KEY (IDENCLOS,IDANIMAL,DATEENTREE) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE HISTORIQUEENCLOS
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_HISTORIQUEENCLOS_ENCLOS
     ON HISTORIQUEENCLOS (IDENCLOS ASC);

CREATE  INDEX I_FK_HISTORIQUEENCLOS_ANIMAUX
     ON HISTORIQUEENCLOS (IDANIMAL ASC);

# -----------------------------------------------------------------------------
#       TABLE : COMPOSITIONREGIME
# -----------------------------------------------------------------------------

CREATE TABLE  COMPOSITIONREGIME
 (
   IDALIMENT INTEGER(2) NOT NULL  ,
   IDREGIME INTEGER(2) NOT NULL  ,
   QUANTITE INTEGER(2) NULL  
   , PRIMARY KEY (IDALIMENT,IDREGIME) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE COMPOSITIONREGIME
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_COMPOSITIONREGIME_ALIMENTS
     ON COMPOSITIONREGIME (IDALIMENT ASC);

CREATE  INDEX I_FK_COMPOSITIONREGIME_REGIME
     ON COMPOSITIONREGIME (IDREGIME ASC);

# -----------------------------------------------------------------------------
#       TABLE : REPARTITIONESPECES
# -----------------------------------------------------------------------------

CREATE TABLE  REPARTITIONESPECES
 (
   IDLOCALISATION INTEGER(2) NOT NULL  ,
   IDESPECE INTEGER(2) NOT NULL  
   , PRIMARY KEY (IDLOCALISATION,IDESPECE) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE REPARTITIONESPECES
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_REPARTITIONESPECES_LOCALISATIONS
     ON REPARTITIONESPECES (IDLOCALISATION ASC);

CREATE  INDEX I_FK_REPARTITIONESPECES_ESPECES
     ON REPARTITIONESPECES (IDESPECE ASC);


# -----------------------------------------------------------------------------
#       CREATION DES REFERENCES DE TABLE
# -----------------------------------------------------------------------------


ALTER TABLE ESPECES 
  ADD FOREIGN KEY FK_ESPECES_REGIME (IDREGIME)
      REFERENCES REGIME (IDREGIME) ;


ALTER TABLE ESPECES 
  ADD FOREIGN KEY FK_ESPECES_ANIMAUX (IDANIMAL)
      REFERENCES ANIMAUX (IDANIMAL) ;


ALTER TABLE ALIMENTS 
  ADD FOREIGN KEY FK_ALIMENTS_ALIMENTS (IDALIMENT_SUBSTITUT)
      REFERENCES ALIMENTS (IDALIMENT) ;


ALTER TABLE SOIGNEURS 
  ADD FOREIGN KEY FK_SOIGNEURS_ENCLOS (IDENCLOS)
      REFERENCES ENCLOS (IDENCLOS) ;


ALTER TABLE APPARTENIRFAMILLE 
  ADD FOREIGN KEY FK_APPARTENIRFAMILLE_ESPECES (IDESPECE)
      REFERENCES ESPECES (IDESPECE) ;


ALTER TABLE APPARTENIRFAMILLE 
  ADD FOREIGN KEY FK_APPARTENIRFAMILLE_FAMILLES (IDFAMILLE)
      REFERENCES FAMILLES (IDFAMILLE) ;


ALTER TABLE APPARTENIRFAMILLE 
  ADD FOREIGN KEY FK_APPARTENIRFAMILLE_FAMILLES1 (IDFAMILLE_1)
      REFERENCES FAMILLES (IDFAMILLE) ;


ALTER TABLE HISTORIQUEENCLOS 
  ADD FOREIGN KEY FK_HISTORIQUEENCLOS_ENCLOS (IDENCLOS)
      REFERENCES ENCLOS (IDENCLOS) ;


ALTER TABLE HISTORIQUEENCLOS 
  ADD FOREIGN KEY FK_HISTORIQUEENCLOS_ANIMAUX (IDANIMAL)
      REFERENCES ANIMAUX (IDANIMAL) ;


ALTER TABLE COMPOSITIONREGIME 
  ADD FOREIGN KEY FK_COMPOSITIONREGIME_ALIMENTS (IDALIMENT)
      REFERENCES ALIMENTS (IDALIMENT) ;


ALTER TABLE COMPOSITIONREGIME 
  ADD FOREIGN KEY FK_COMPOSITIONREGIME_REGIME (IDREGIME)
      REFERENCES REGIME (IDREGIME) ;


ALTER TABLE REPARTITIONESPECES 
  ADD FOREIGN KEY FK_REPARTITIONESPECES_LOCALISATIONS (IDLOCALISATION)
      REFERENCES LOCALISATIONS (IDLOCALISATION) ;


ALTER TABLE REPARTITIONESPECES 
  ADD FOREIGN KEY FK_REPARTITIONESPECES_ESPECES (IDESPECE)
      REFERENCES ESPECES (IDESPECE) ;

