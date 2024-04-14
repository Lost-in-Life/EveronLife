class EL_CharacterSelection : ChimeraMenuBase
{
	protected Widget m_wRoot;
	protected SCR_ButtonTextComponent comp;
	IEntity entity;

	protected Widget m_wConfirmButton;
	protected SCR_InputButtonComponent m_Confirm;

	ref ScriptInvoker m_OnConfirm = new ScriptInvoker();
	
	//------------------------------------------------------------------------------------------------
	protected override void OnMenuOpen()
	{
		//super.OnMenuOpen();
		Widget m_wRoot = GetRootWidget();
		if (!m_wRoot)
		{
			Print("Error in creating Character Selection screen", LogLevel.ERROR);
			return;
		}
		
		// Confirm button
		m_wConfirmButton = m_wRoot.FindAnyWidget("Create");
		if(m_wConfirmButton)
		{
			m_Confirm = SCR_InputButtonComponent.FindComponent(m_wConfirmButton);
			if (m_Confirm)
				m_Confirm.m_OnActivated.Insert(sendCreateChar);
		}
		
		comp = SCR_ButtonTextComponent.GetButtonText("Create", m_wRoot);
		if (comp)
		{
			GetGame().GetWorkspace().SetFocusedWidget(comp.GetRootWidget());
			comp.m_OnClick.Insert(sendCreateChar);
		}
		
		InputManager inputManager = GetGame().GetInputManager();
		if (inputManager)
		{
			// this is for the menu/dialog to close when pressing ESC
			// an alternative is to have a button with the SCR_NavigationButtonComponent component
			// and its Action Name field set to MenuBack - this would activate the button on ESC press
			inputManager.AddActionListener("MenuOpen", EActionTrigger.DOWN, Close);
			inputManager.AddActionListener("MenuBack", EActionTrigger.DOWN, Close);
			#ifdef WORKBENCH // in Workbench, F10 is used because ESC closes the preview
				inputManager.AddActionListener("MenuOpenWB", EActionTrigger.DOWN, Close);
				inputManager.AddActionListener("MenuBackWB", EActionTrigger.DOWN, Close);
			#endif
		}
	}

	//------------------------------------------------------------------------------------------------
	protected override void OnMenuClose()
	{
		// here we clean action listeners added above as the good practice wants it
		InputManager inputManager = GetGame().GetInputManager();
		if (inputManager)
		{
			inputManager.RemoveActionListener("MenuOpen", EActionTrigger.DOWN, Close);
			inputManager.RemoveActionListener("MenuBack", EActionTrigger.DOWN, Close);
			#ifdef WORKBENCH
				inputManager.RemoveActionListener("MenuOpenWB", EActionTrigger.DOWN, Close);
				inputManager.RemoveActionListener("MenuBackWB", EActionTrigger.DOWN, Close);
			#endif
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void ChangeText()
	{
		m_wRoot = GetRootWidget();
		if (!m_wRoot)
			return;
	}
	
	void sendCreateChar()
	{

		// For getting the Account object of the player that pressed the button.
		int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
		EL_PlayerAccount account = EL_PlayerAccountManager.GetInstance().GetFromCache(localPlayerId);
		
		// Gets random character prefab from the config.
		ResourceName prefab = "{CE23D4366B47E9B9}Prefabs/Characters/Presets/White_Male_01.et";
		if (prefab)
			{
			
				EL_PlayerCharacter activeCharacter = EL_PlayerCharacter.Create(prefab, "Test", "Test");
				account.AddCharacter(activeCharacter, true);
			}
		else
			{
				Print("Could not create new character, no default prefabs configured. Go to EL_GameModeRoleplay > EL_RespawnSytemComponent and add at least one.", LogLevel.ERROR);
				return;
			}
		
		m_OnConfirm.Invoke();
		//CloseAnimated();
		Close();
	}
}