/*
 * Com_Helper.h
 *
 *  Created on: Oct 25, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_COM_HELPER_H_
#define INCLUDE_COM_HELPER_H_

#define GET_IPdu(IPduId) (&(ComConfig->ComIPdu[IPduId]))
#define GET_Signal(SignalId) (&(ComConfig->ComSignal[SignalId]))

#endif /* INCLUDE_COM_HELPER_H_ */
