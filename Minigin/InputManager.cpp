#include <SDL.h>
#include <iostream>

#include "Gamepad.h"
#include "InputManager.h"

namespace dae 
{
    class InputManager::Impl 
    {
    public:
        Impl() : m_Gamepad(nullptr)
        {
            m_Gamepad = std::make_unique<Gamepad>(0); 
        }

        bool ProcessInput()
        {
            m_Gamepad->Update();

            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    return false;
                }

                if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
                {
                    auto key = e.key.keysym.sym;
                    KeyState state = (e.type == SDL_KEYDOWN) ? KeyState::Down : KeyState::Up;

                    //check if the key has commands bound to it
                    if (m_KeyCommands.find(key) != m_KeyCommands.end())
                    {
                        //iterate over all commands bound to this key
                        for (const auto& [boundState, command] : m_KeyCommands[key])
                        {
                            //execute the command if the key matches the state
                            if (boundState == state)
                            {
                                command->Execute();
                            }
                        }
                    }
                }
            }

            //process controller input
            for (const auto& [button, commands] : m_ControllerCommands)
            {
                for (const auto& [state, command] : commands)
                {
                    //check if the button state matches and execute the command
                    if (IsButtonState(button, state))
                    {
                        command->Execute();
                    }
                }
            }

            return true;
        }

        void BindCommand(SDL_Keycode key, KeyState state, std::shared_ptr<Command> command) 
        {
            m_KeyCommands[key].emplace_back(state, command);
        }

        void BindCommand(WORD button, KeyState state, std::shared_ptr<Command> command) 
        {
            m_ControllerCommands[static_cast<WORD>(button)].emplace_back(state, command);
        }
        void ClearAll()
        {
            m_KeyCommands.clear();
            m_ControllerCommands.clear();
        }
        bool IsButtonState(WORD button, KeyState state) const 
        {
            if (m_Gamepad == nullptr)
            {
                return false;
            }
            
            switch (state) 
            {
            case KeyState::Down:
                return m_Gamepad->IsButtonDown(button);
            case KeyState::Up:
                return m_Gamepad->IsButtonUp(button);
            case KeyState::Pressed:
                return m_Gamepad->IsButtonPressed(button);
            default:
                return false;
            }
        }

    private:
        std::unique_ptr<Gamepad> m_Gamepad{};
        std::unordered_map<SDL_Keycode, std::vector<std::pair<KeyState, std::shared_ptr<Command>>>> m_KeyCommands;
        std::unordered_map<WORD, std::vector<std::pair<KeyState, std::shared_ptr<Command>>>> m_ControllerCommands;

    };

    InputManager::InputManager() : m_Impl(std::make_unique<Impl>()) {}


    InputManager::~InputManager() = default;

    bool InputManager::ProcessInput()
    {
        return m_Impl->ProcessInput();
    }

    void InputManager::BindCommand(SDL_Keycode key, KeyState state, std::shared_ptr<Command> command)
    {
        m_Impl->BindCommand(key, state, command);
    }

    void InputManager::BindCommand(GamepadButton button, KeyState state, std::shared_ptr<Command> command)
    {
        m_Impl->BindCommand(static_cast<WORD>(button), state, command);
    }
    void InputManager::ClearAllBindings()
    {
        m_Impl->ClearAll();
    }

}
