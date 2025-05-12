#pragma once
#include <iostream>

#include "Command.h"

namespace dae
{
	class TestCommand final : public Command
	{
		void Execute() override
		{
			std::cout << "Test command executed!" << std::endl;
		}
	};
}
