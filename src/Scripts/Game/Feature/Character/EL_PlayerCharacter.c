class EL_PlayerCharacter
{
	protected string m_sId;
	protected ResourceName m_rPrefab;
	protected string m_firstname;
	protected string m_lastname;
	protected ref array<ref EL_CharacterLicence> m_aLicences = {};

	//------------------------------------------------------------------------------------------------
	string GetId()
	{
		return m_sId;
	}

	//------------------------------------------------------------------------------------------------
	ResourceName GetPrefab()
	{
		return m_rPrefab;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetFirstname()
	{
		return m_firstname;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetLastname()
	{
		return m_lastname;
	}

	//------------------------------------------------------------------------------------------------
	static EL_PlayerCharacter Create(ResourceName prefab, string firstname, string lastname)
	{
		EL_PlayerCharacter character();
		character.m_sId = EPF_PersistenceIdGenerator.Generate();
		character.m_rPrefab = prefab;
		character.m_firstname = firstname;
		character.m_lastname = lastname;
		return character;
	}
	
	//------------------------------------------------------------------------------------------------
	void AddLicenceToCharacter(notnull EL_CharacterLicence licence)
	{
		Print("2" + licence.GetLicence());
		m_aLicences.Insert(licence);
	}
	
	//------------------------------------------------------------------------------------------------
	void RemoveLicenceFromCharacter(notnull EL_CharacterLicence licence)
	{
		m_aLicences.RemoveItemOrdered(licence);
	}
	
	//------------------------------------------------------------------------------------------------
	bool HasLicences()
	{
		return !m_aLicences.IsEmpty();
	}
	
	//------------------------------------------------------------------------------------------------
	array<EL_CharacterLicence> GetLicences()
	{
		array<EL_CharacterLicence> results();
		results.Reserve(m_aLicences.Count());
		foreach (EL_CharacterLicence licence : m_aLicences)
		{
			Print("3" + licence.GetLicence());
			results.Insert(licence);
		}
		return results;
	}
	
	//------------------------------------------------------------------------------------------------
	bool HasLicencesCheckByName(string licenceName)
	{
		foreach (EL_CharacterLicence licence : m_aLicences)
		{
			if(licence.GetLicence() == licenceName)
			{
				return true;
			}
		}
		return false;
	}
	
	EL_CharacterLicence GetLicenceByName(string licenceName)
	{
		foreach (EL_CharacterLicence licence : m_aLicences)
		{
			if(licence.GetLicence() == licenceName)
			{
				return licence;
			}
		}
		return null;
	}


};