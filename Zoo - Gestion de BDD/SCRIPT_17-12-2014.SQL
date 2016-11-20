DROP DATABASE IF EXISTS MLR9;

CREATE DATABASE IF NOT EXISTS MLR9;
USE MLR9;
# -----------------------------------------------------------------------------
#       TABLE : ENCLOS
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS ENCLOS
 (
   IDENCLOS INTEGER(2) NOT NULL  ,
   IDSOIGNEUR INTEGER(2) NULL  ,
   CODEE CHAR(3) NULL  ,
   NOME CHAR(63) NULL  ,
   SURFACEE INTEGER(2) NULL  ,
   TYPEE CHAR(63) NULL  
   , PRIMARY KEY (IDENCLOS) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE ENCLOS
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_ENCLOS_SOIGNEURS
     ON ENCLOS (IDSOIGNEUR ASC);

# -----------------------------------------------------------------------------
#       TABLE : ESPECES
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS ESPECES
 (
   IDESPECE INTEGER(2) NOT NULL  ,
   IDFAMILLE INTEGER(2) NULL  ,
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


CREATE  INDEX I_FK_ESPECES_FAMILLES
     ON ESPECES (IDFAMILLE ASC);

# -----------------------------------------------------------------------------
#       TABLE : ALIMENTS
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS ALIMENTS
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

CREATE TABLE IF NOT EXISTS SOIGNEURS
 (
   IDSOIGNEUR INTEGER(2) NOT NULL  ,
   NOMS CHAR(63) NULL  ,
   PRENOMS CHAR(63) NULL  ,
   DATES DATE NULL  
   , PRIMARY KEY (IDSOIGNEUR) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : FAMILLES
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS FAMILLES
 (
   IDFAMILLE INTEGER(2) NOT NULL  ,
   NOMSCIF CHAR(127) NULL  
   , PRIMARY KEY (IDFAMILLE) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : DATE_
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS DATE_
 (
   DATEENTRE DATE NOT NULL  
   , PRIMARY KEY (DATEENTRE) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : ANIMAUX
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS ANIMAUX
 (
   IDANIMAL INTEGER(2) NOT NULL  ,
   IDESPECE INTEGER(2) NULL  ,
   NOMA CHAR(63) NULL  ,
   SEXEA ENUM{'M', 'F'} NULL  ,
   DATENAISSANCE DATE NULL  ,
   DATEARRIVE DATE NULL  
   , PRIMARY KEY (IDANIMAL) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE ANIMAUX
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_ANIMAUX_ESPECES
     ON ANIMAUX (IDESPECE ASC);

# -----------------------------------------------------------------------------
#       TABLE : HISTORIQUEENCLOS
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS HISTORIQUEENCLOS
 (
   IDANIMAL INTEGER(2) NOT NULL  ,
   IDENCLOS INTEGER(2) NOT NULL  ,
   DATEENTRE DATE NOT NULL  ,
   DATESORTIE DATE NULL  
   , PRIMARY KEY (IDANIMAL,IDENCLOS,DATEENTRE) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE HISTORIQUEENCLOS
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_HISTORIQUEENCLOS_DATE_
     ON HISTORIQUEENCLOS (DATEENTRE ASC);

CREATE  INDEX I_FK_HISTORIQUEENCLOS_ENCLOS
     ON HISTORIQUEENCLOS (IDENCLOS ASC);

CREATE  INDEX I_FK_HISTORIQUEENCLOS_ANIMAUX
     ON HISTORIQUEENCLOS (IDANIMAL ASC);

# -----------------------------------------------------------------------------
#       TABLE : REGIME
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS REGIME
 (
   IDREGIME INTEGER(2) NOT NULL  ,
   IDESPECE INTEGER(2) NOT NULL  ,
   SEXER ENUM{'M', 'F'} NULL  
   , PRIMARY KEY (IDREGIME) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       INDEX DE LA TABLE REGIME
# -----------------------------------------------------------------------------


CREATE  INDEX I_FK_REGIME_ESPECES
     ON REGIME (IDESPECE ASC);

# -----------------------------------------------------------------------------
#       TABLE : LOCALISATIONS
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS LOCALISATIONS
 (
   IDLOCALISATION INTEGER(2) NOT NULL  ,
   CODEL CHAR(3) NULL  ,
   NOML CHAR(127) NULL  
   , PRIMARY KEY (IDLOCALISATION) 
 ) 
 comment = "";

# -----------------------------------------------------------------------------
#       TABLE : COMPOSITIONREGIME
# -----------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS COMPOSITIONREGIME
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

CREATE TABLE IF NOT EXISTS REPARTITIONESPECES
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


ALTER TABLE ENCLOS 
  ADD FOREIGN KEY FK_ENCLOS_SOIGNEURS (IDSOIGNEUR)
      REFERENCES SOIGNEURS (IDSOIGNEUR) ;


ALTER TABLE ESPECES 
  ADD FOREIGN KEY FK_ESPECES_FAMILLES (IDFAMILLE)
      REFERENCES FAMILLES (IDFAMILLE) ;


ALTER TABLE ALIMENTS 
  ADD FOREIGN KEY FK_ALIMENTS_ALIMENTS (IDALIMENT_SUBSTITUT)
      REFERENCES ALIMENTS (IDALIMENT) ;


ALTER TABLE ANIMAUX 
  ADD FOREIGN KEY FK_ANIMAUX_ESPECES (IDESPECE)
      REFERENCES ESPECES (IDESPECE) ;


ALTER TABLE HISTORIQUEENCLOS 
  ADD FOREIGN KEY FK_HISTORIQUEENCLOS_DATE_ (DATEENTRE)
      REFERENCES DATE_ (DATEENTRE) ;


ALTER TABLE HISTORIQUEENCLOS 
  ADD FOREIGN KEY FK_HISTORIQUEENCLOS_ENCLOS (IDENCLOS)
      REFERENCES ENCLOS (IDENCLOS) ;


ALTER TABLE HISTORIQUEENCLOS 
  ADD FOREIGN KEY FK_HISTORIQUEENCLOS_ANIMAUX (IDANIMAL)
      REFERENCES ANIMAUX (IDANIMAL) ;


ALTER TABLE REGIME 
  ADD FOREIGN KEY FK_REGIME_ESPECES (IDESPECE)
      REFERENCES ESPECES (IDESPECE) ;


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

