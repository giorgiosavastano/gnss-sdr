/*!
 * \file control_message_factory.cc
 * \brief Implementation of a Control Message Factory
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2011  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#include "control_message_factory.h"

#include <glog/log_severity.h>
#include <glog/logging.h>

#include <vector>

#include "string.h"

using google::LogMessage;

//! Constructor
ControlMessageFactory::ControlMessageFactory()
{}

//! Destructor
ControlMessageFactory::~ControlMessageFactory()
{}

gr_message_sptr ControlMessageFactory::GetQueueMessage(unsigned int who, unsigned int what) {

	ControlMessage *control_message = new ControlMessage;

	control_message->who = who;
	control_message->what = what;

	gr_message_sptr queue_message = gr_make_message(0, 0, 0, sizeof(ControlMessage));
	memcpy(queue_message->msg(), control_message, sizeof(ControlMessage));

	delete control_message;

	return queue_message;
}

std::vector<ControlMessage*>* ControlMessageFactory::GetControlMessages(gr_message_sptr queue_message) {

	std::vector<ControlMessage*>* control_messages = new std::vector<ControlMessage*>();
	unsigned int control_messages_count = queue_message->length() / sizeof(ControlMessage);
	if(queue_message->length() % sizeof(ControlMessage) != 0) {
		LOG_AT_LEVEL(WARNING) << "Queue message has size " << queue_message->length() << " which is not" <<
		" multiple of control message size " << sizeof(ControlMessage);
		LOG_AT_LEVEL(WARNING) << "Ignoring this queue message to prevent unexpected results.";
		return control_messages;
	}
	for(unsigned int i=0;i<control_messages_count;i++) {
		control_messages->push_back(new ControlMessage);
		memcpy(control_messages->at(i), queue_message->msg() + (i*sizeof(ControlMessage)), sizeof(ControlMessage));
	}

	return control_messages;
}

