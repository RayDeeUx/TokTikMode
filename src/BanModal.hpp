/*
This file is part of TokTikMode.

TokTikMode is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with TokTikMode; if not, see
<https://www.gnu.org/licenses/>.
*/

/* Source code is self-authored. --Erymanthus */

#pragma once

#define BAN_MODAL_TITLE "Sorry, TokTik isn't\navailable right now"
#define BAN_MODAL_TEXT "A law banning TokTik has been enacted in the U.S. Unfortunately, that means you can't use TokTik right now.\n\nWe are fortunate that President Trump has indicated that he will work with us on a solution to reinstate TokTik once he takes office. Stay tuned!"

class BanModal final : public FLAlertLayer {
protected:
	bool init() override;
public:
	static BanModal* create();
};