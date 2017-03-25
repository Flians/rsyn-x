/* Copyright 2014-2017 Rsyn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhysicalLibraryPin.h
 * Author: jucemar
 *
 * Created on 13 de Setembro de 2016, 21:06
 */

#ifndef PHYSICALDESIGN_PHYSICALLIBRARYPIN_H
#define PHYSICALDESIGN_PHYSICALLIBRARYPIN_H

namespace Rsyn {

class PhysicalLibraryPin : public Proxy<PhysicalLibraryPinData> {
	friend class PhysicalDesign;
protected:
	//! @brief Constructs a Rsyn::PhysicalLibraryPin object with a pointer to Rsyn::PhysicalLibraryPinData.
	PhysicalLibraryPin(PhysicalLibraryPinData * data) : Proxy(data) {}
public:
	//! @brief Constructs a Rsyn::PhysicalLibraryPin object with a null pointer to Rsyn::PhysicalLibraryPinData.
	PhysicalLibraryPin() : Proxy(nullptr) {}
	//! @brief Constructs a Rsyn::PhysicalLibraryPin object with a null pointer to Rsyn::PhysicalLibraryPinData.
	PhysicalLibraryPin(std::nullptr_t) : Proxy(nullptr) {}

	//! @brief Returns the pin rectangular boundaries defined at 2015 ICCAD contest.
	Bounds getICCADBounds();
	//! @brief Returns the pin rectangular boundaries reference defined at 2015 ICCAD contest.
	const Bounds & getICCADBounds() const;
	//! @brief Returns a vector reference to PhysicalPinPort objects related to the PhysicalLibraryPin.
	std::vector<PhysicalPinPort> & allPinPorts();
	//! @brief Returns a constant vector reference to PhysicalPinPort objects related to the PhysicalLibraryPin.
	const std::vector<PhysicalPinPort> & allPinPorts() const;
	//! @brief Returns an integer number that is the total number of PhysicalPinPort related to the PhysicalLibraryPin.
	std::size_t getNumPinPorts() const;
	//! @brief Returns true if PhysicalLibraryPin has PhysicalPinPort objects. Otherwise, returns false.
	bool hasPinPorts() const;
	//! @brief Returns true if PhysicalLibraryPin has no PhysicalPinPort objects. Otherwise, returns false.
	bool isPinPortsEmpty() const;
	//! @brief Returns an enum indicating the pin direction. 
	PhysicalPinDirection getPinDirection() const;
	
}; // end class  

} // end namespace 

#endif /* PHYSICALDESIGN_PHYSICALLIBRARYPIN_H */

