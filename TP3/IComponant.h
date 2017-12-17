#pragma once

namespace tp3
{

	class IComponant
	{
	public:
		virtual void bouger() = 0;
		virtual void arreter() = 0;
		virtual void retirer(int i) = 0;
	};
}