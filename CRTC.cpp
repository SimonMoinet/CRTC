/**
 * \mainpage Classe CRTC
 * \author Simon Moinet
 * \date Mars 2015
 *
 * \file CRTC.h
 * Déclaration de la classe CRTC
 * \class CRTC
 * \brief Cette classe permet
 */

#ifndef CRTC_CPP
#define CRTC_CPP

#include "/home/jam/Bureau/C++/Classes/CI2C/CI2C.h"

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

		void setRTCHeures(int heures);
		void setRTCHeures(int heures)

};

#endif // CRTC_CPP
