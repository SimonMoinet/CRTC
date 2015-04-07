/**
 * \mainpage Classe CRTC
 * \author Simon Moinet
 * \date Mars 2015
 *
 * \file CRTC.h
 * Déclaration de la classe CRTC
 * \class CRTC
 */

#ifndef CRTC_H
#define CRTC_H

#include "CI2C/CI2C.h"


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
			MODE_DOUZE, ///< Mode 12H : system horaire 12 heure (de 1h à 12h avec AM/PM)
			MODE_VINGT_QUATRE ///< Mode 24H : system horaire 24 heure (de 0h à 23h)
		};

		/**
		 * \enum PERIODE_HORAIRE
		 * Cette enumeration liste les periodes horaires AM et PM
		 */
		enum class PERIODE_HORAIRE : __u8
		{
			AM, ///< AM : De 0 heure à 11 heure
			PM ///< PM : De 12 heure à 23 heure
		};

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
			MODE_HEURE mode; ///< mode des heures
			PERIODE_HORAIRE pHoraire; ///< Contient AM/PM si on est en mode 12H
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


		/**
		 * \class ErreurModeHeure
		 */
		class ErreurModeHeure : public exception {
			private:
				CRTC::MODE_HEURE m_mode;

			public:
				ErreurModeHeure(MODE_HEURE mode):m_mode(mode) {};
				virtual const char* what() const noexcept {
					string temp = "Le mode des heures ne correspond pas : mode ";
					if( m_mode == MODE_HEURE::MODE_DOUZE )
						temp += "12H";
					else
						temp += "24H";
					return temp.c_str();
				};
		};

	private:
		/**
		 * \Brief Methode getRTCValReg
		 * Cette methode permet de récuperer la valeur d'un registre de l'horloge RTC
		 * 
		 * \param[in] reg : le registre dont on veux récuperer la valeur
		 * \return un entier contenant la valeur du registre
		 */
		int getRTCValReg(__u8 reg);

		/**
		 * \Brief Methode setRTCValReg
		 * Cette methode permet de définir la valeur d'un registre de l'horloge RTC
		 * 
		 * \param[in] val : la valeur que l'on veux mettre dans le registre
		 * \param[in] reg : le registre dont on veux modifier la valeur
		 */
		void setRTCValReg(__u8 val, __u8 reg);

	public:

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

		/**
		 * \brief Methode setRTCHeures
		 *
		 * Cette methode permet de changer la valeur du registre correspondant aux heures
		 * de l'horloge RTC lorsqu'on utilise le mode 12H
		 *
		 * \param[in] heures La nouvelle valeur des heures que l'on veux mettre dans le registre
		 * \param[in] pHoraire : la période horaire 
		 */
		void setRTCHeures(int heures, PERIODE_HORAIRE pHoraire);

		/**
		 * \brief Methode setRTCJourSemaine
		 *
		 * Cette methode permet de changer la valeur du registre correspondant aux jour de la semaine
		 * de l'horloge RTC
		 *
		 * \param[in] jour_semaine La nouvelle valeur du jour de la semaine que l'on veux mettre dans le registre
		 */
		void setRTCJourSemaine(int jour_semaine);

		/**
		 * \brief Methode setRTCJourMois
		 *
		 * Cette methode permet de changer la valeur du registre correspondant aux jour du mois
		 * de l'horloge RTC
		 *
		 * \param[in] jour_mois La nouvelle valeur du jour du mois que l'on veux mettre dans le registre
		 */
		void setRTCJourMois(int jour_mois);

		/**
		 * \brief Methode setRTCMois
		 *
		 * Cette methode permet de changer la valeur du registre correspondant aux mois
		 * de l'horloge RTC
		 *
		 * \param[in] mois La nouvelle valeur du mois que l'on veux mettre dans le registre
		 */
		void setRTCMois(int mois);

		/**
		 * \brief Methode setRTCAnnee
		 *
		 * Cette methode permet de changer la valeur du registre correspondant aux années
		 * de l'horloge RTC
		 *
		 * \param[in] annee La nouvelle valeur de l'annee que l'on veux mettre dans le registre
		 */
		void setRTCAnnee(int annee);

		/**
		* \brief Methode setRTCDate
		*
		* Cette methode permet de mettre a jour tous les champs concernant la date de l'horloge
		* RTC
		*
		* \param[in] date : une structure qui contient toutes les informations sur la date
		*/
		void setRTCDate(str_date date);
		/**
		* \brief Methode setRTCTime
		*
		* Cette methode permet de mettre a jour tous les champs concernant les heures de l'horloge
		* RTC
		*
		* \param[in] heure : une structure qui contient toutes les informations sur l'heure
		*/
		void setRTCTime(str_heure heure);
		/**
		* \brief Methode setRTCDateTime
		*
		* Cette methode permet de mettre a jour tous les champs concernant l'heure et la date
		* de l'horloge RTC
		*
		* \param[in] dateHeure : une structure qui contient toutes les informations sur l'heure et la date
		*/
		void setRTCDateTime(str_dateHeure dateHeure);
		

		// ######################################################
		// # METHODES DE RECUPERATION DES VALEURS DES REGISTRES #
		// # DE L'HORLOGE RTC 									#
		// ######################################################

		/**
		 * \brief Methode getRTCSecondes
		 *
		 * Cette methode permet de récuperer la valeur du registre des secondes
		 * de l'horloge RTC
		 *
		 * \return int : la valeur des secondes
		 */
		int getRTCSecondes();

		/**
		 * \brief Methode getRTCMinutes
		 *
		 * Cette methode permet de récuperer la valeur du registre des minutes
		 * de l'horloge RTC
		 *
		 * \return int : la valeur des minutes
		 */
		int getRTCMinutes();

		/**
		 * \brief Methode getRTCHeures
		 *
		 * Cette methode permet de récuperer la valeur du registre des heures pour le mode
		 * 12H de l'horloge RTC
		 *
		 * \param[in/out] mode : la periode horaire 
		 * \return int : la valeur des heures
		 */
		int getRTCHeures(PERIODE_HORAIRE &pHoraire);

		/**
		 * \brief Methode getRTCHeures
		 *
		 * Cette methode permet de récuperer la valeur du registre des heures pour le mode
		 * 24H de l'horloge RTC
		 *
		 * \return int : la valeur des heures
		 */
		int getRTCHeures();

		/**
		 * \brief Methode getRTCJourSemaine
		 *
		 * Cette methode permet de récuperer la valeur du registre du jour de la semaine
		 * de l'horloge RTC
		 *
		 * \return int : la valeur du jour de la semaine
		 */
		int getRTCJourSemaine();

		/**
		 * \brief Methode getRTCJourMois
		 *
		 * Cette methode permet de récuperer la valeur du registre du jour du mois
		 * de l'horloge RTC
		 *
		 * \return int : la valeur du jour du mois
		 */
		int getRTCJourMois();

		/**
		 * \brief Methode getRTCMois
		 *
		 * Cette methode permet de récuperer la valeur du registre du mois
		 * de l'horloge RTC
		 *
		 * \return int : la valeur du mois
		 */
		int getRTCMois();

		/**
		 * \brief Methode getRTCAnnee
		 *
		 * Cette methode permet de récuperer la valeur du registre des annee
		 * de l'horloge RTC
		 *
		 * \return int : la valeur des annee
		 */
		int getRTCAnnee();

		/**
		* \brief Methode getRTCDate
		*
		* Cette methode permet de récuperer une structure contenant la valeur
		* des registres de la date de l'horloge RTC
		*
		* \return str_date : la structure contenant la date
		*/
		str_date getRTCDate();
		/**
		* \brief Methode getRTCTime
		*
		* Cette methode permet de récuperer une structure contenant la valeur
		* des registres des heures de l'horloge RTC
		*
		* \return str_date : la structure contenant l'heure
		*/
		str_heure getRTCTime();
		/**
		* \brief Methode getRTCDateTime
		*
		* Cette methode permet de récuperer une structure contenant la valeur
		* des registres de la date et de l'heures de l'horloge RTC
		*
		* \return str_date : la structure contenant la date et l'heure
		*/
		str_dateHeure getRTCDateHeure();

		/**
		 * \brief Methode getRTCModeHeure
		 *
		 * Cette methode permet de récuperer le mode des heures
		 * de l'horloge RTC
		 *
		 * \return int : le mode des heures de l'horloge RTC
		 */
		MODE_HEURE getRTCModeHeure();


};


#endif // CRTC_H