class EL_PlayerAccount : EPF_PersistentScriptedState
{
	/*protected*/ ref array<ref EL_PlayerCharacter> m_aCharacters = {};
	/*protected*/ int m_iActiveCharacterIdx;

	//------------------------------------------------------------------------------------------------
	void AddCharacter(notnull EL_PlayerCharacter character, bool setAsActive = false)
	{
		int idx = m_aCharacters.Insert(character);
		if (setAsActive)
			m_iActiveCharacterIdx = idx;
	}

	//------------------------------------------------------------------------------------------------
	void RemoveCharacter(notnull EL_PlayerCharacter character)
	{
		m_aCharacters.RemoveItemOrdered(character);
	}

	//------------------------------------------------------------------------------------------------
	bool HasCharacters()
	{	
		return !m_aCharacters.IsEmpty();
	}

	//------------------------------------------------------------------------------------------------
	array<EL_PlayerCharacter> GetCharacters()
	{
		array<EL_PlayerCharacter> results();
		results.Reserve(m_aCharacters.Count());
		foreach (EL_PlayerCharacter character : m_aCharacters)
		{
			results.Insert(character);
		}
		return results;
	}

	//------------------------------------------------------------------------------------------------
	EL_PlayerCharacter GetActiveCharacter()
	{
		if (!m_aCharacters.IsEmpty())
			return m_aCharacters.Get(m_iActiveCharacterIdx);

		return null;
	}

	//------------------------------------------------------------------------------------------------
	void SetActiveCharacter(notnull EL_PlayerCharacter character)
	{
		m_iActiveCharacterIdx = m_aCharacters.Find(character);
	}

	//------------------------------------------------------------------------------------------------
	static EL_PlayerAccount Create(string playerUid)
	{
		EL_PlayerAccount account();
		account.SetPersistentId(playerUid);
		return account;
	}

};

