/**
 * \mainpage Classe CRTC
 * \author Simon Moinet
 * \date Mars 2015
 *
 * \file CRTC.h
 * Déclaration de la classe CRTC
 * \class CRTC
 */

#ifndef CRTC_CPP
#define CRTC_CPP

#include "CI2C/CI2C.h"

// ##############
// # STRUCTURES #
// ##############

/**
 * \struct str_date
 * \brief Contient les informations sur une date
 */
struct str_date
{
	int jour_semaine; ///< numero du jour dans la semaine (ex: 1=Lundi, 2=Mardi, ...)
	int jour_mois; ///< numero du jour dans le mois
	int mois; ///< numero du mois
	int annee; ///< numero de l'annee
};

/**
 * \struct str_heure
 * \brief Contient les informations sur une heure
 */
struct str_heure
{
	int secondes; ///< valeur des secondes
	int minutes; ///< valeur des minutes
	int heures; ///< valeur des heures
	CRTC::PERIODE_HORAIRE pHoraire = NULL; ///< Contient AM/PM si on est en mode 12H
};

/**
 * \struct
 * \brief Contient les informations sur une heure et sur une date
 */
struct str_dateHeure
{
	str_date date; ///< structure contenant les informations sur la date
	str_heure heure; ///< structure contenant les informations sur l'heure
};


// ################
// # CLASSES CRTC #
// ################

class CRTC : public CI2C
{
	public:
		// ###############
		// # ENUMERATION #
		// ###############
		
		/**
		 * \enum ADDR_REG
		 * Cette enumeration liste les registres de l'horloge RTC
		 */
		enum class ADDR_REG : __u8
		{
			SECONDES, ///< 0x01 : Registre contenant la valeur des secondes
			MINUTES, ///< 0x01 : Registre contenant la valeur des minutes
			HEURES, ///< 0x02 : Registre contenant la valeur des heures
			JOUR_SEMAINE, ///< 0x03 : Registre contenant le numero du jour de la semaine
			JOUR_MOIS, ///< 0x04 : Registre contenant le numero du jour dans le mois
			MOIS, ///< 0x05 : Registre contenant le numero du mois
			ANNEE ///< 0x06 : Registre contenant la valeur de l'année
		};

		/**
		 * \enum MODE_HEURE
		 * Cette enumeration liste les deux modes des heures de l'horloge RTC
		 */
		enum class MODE_HEURE : __u8
		{
			12H, ///< Mode 12H : system horaire 12 heure (de 1h à 12h avec AM/PM)
			24H ///< Mode 24H : system horaire 24 heure (de 0h à 23h)
		};

		/**
		 * \enum SYSTEM_HORAIRE
		 * Cette enumeration liste les systemes horaires AM et PM
		 */
		enum class PERIODE_HORAIRE : __u8
		{
			AM, ///< AM : De 0 heure à 11 heure
			PM ///< PM : De 12 heure à 23 heure
		};

		// ##############################
		// # CONSTRUCTEUR - DESTRUCTEUR #
		// ##############################
		
		/**
		 * \brief Constructeur de la class CRTC
		 */
		CRTC();

		/**
		 * \brief Destructeur de la classe CRTC
		 */
		~CRTC();

		// ######################################################
		// # METHODES DE MODIFICATION DES VALEURS DES REGISTRES #
		// # DE L'HORLOGE RTC 									#
		// ######################################################

		/**
		 * \brief Methode setRTCSecondes
		 *
		 * Cette Methode permet de changer la valeur du registre correspondant aux secondes
		 * de l'horloge RTC
		 *
		 * \param[in] secondes La nouvelle valeur des secondes que l'on veux mettre dans le registre
		 */
		void setRTCSecondes(int secondes);

		/**
		 * \brief Methode setRTCMinutes
		 *
		 * Cette Methode permet de changer la valeur du registre correspondant aux minutes
		 * de l'horloge RTC
		 *
		 * \param[in] minutes La nouvelle valeur des minutes que l'on veux mettre dans le registre
		 */
		void setRTCMinutes(int minutes);

		/**
		 * \brief Methode setRTCHeures
		 *
		 * Cette methode permet de changer la valeur du registre correspondant aux heures
		 * de l'horloge RTC lorsqu'on utilise le mode 24H
		 *
		 * \param[in] heures La nouvelle valeur des heures que l'on veux mettre dans le registre
		 */
		void setRTCHeures(int heures);
		void setRTCHeures(int heures, PERIODE_HORAIRE pHoraire);
		void setRTCJourSemaine(int jour_semaine);
		void setRTCJourMois(int jour_mois);
		void setRTCMois(int mois);
		void setRTCAnnee(int annee);

		void setRTCDate(str_date date);
		void setRTCTime(str_heure heure);
		void setRTCDateTime(str_dateHeure dateHeure);

		void setModeHeure(MODE_HEURE mode, int heure = 1);

		// ######################################################
		// # METHODES DE RECUPERATION DES VALEURS DES REGISTRES #
		// # DE L'HORLOGE RTC 									#
		// ######################################################

		int getRTCSecondes() const;
		int getRTCMinutes() const;
		int getRTCHeures(MODE_HEURE &mode) const;
		int getRTCJourSemaine() const;
		int getRTCJourMois() const;
		int getRTCMois() const;
		int getRTCAnnee() const;

		str_date getRTCDate() const;
		str_heure getRTCTime() const;
		str_dateHeure getRTCDateHeure() const;

		MODE_HEURE getRTCModeHeure() const;
};

#endif // CRTC_CPP
