#pragma once

#include "CSingleton.hpp"
#include "types.hpp"

#include <string>
#include <memory>
#include <atomic>

#include <json.hpp>

using json = nlohmann::json;


class CChannel
{
public:
	CChannel(ChannelId_t pawn_id, json &data);
	~CChannel() = default;

private:
	const ChannelId_t m_PawnId;

	Snowflake_t
		m_Id,
		m_GuildId;

	bool m_IsPrivate = false;

	std::string
		m_Name,
		m_Topic;

public:
	inline ChannelId_t GetPawnId() const
	{
		return m_PawnId;
	}
	inline Snowflake_t const &GetId() const
	{
		return m_Id;
	}
	inline Snowflake_t const &GetGuildId() const
	{
		return m_GuildId;
	}
	inline std::string const &GetName() const
	{
		return m_Name;
	}
	inline std::string const &GetTopic() const
	{
		return m_Topic;
	}

	void SendMessage(std::string &&msg);

};


class CChannelManager : public CSingleton<CChannelManager>
{
	friend class CSingleton<CChannelManager>;
private:
	CChannelManager() = default;
	~CChannelManager() = default;

private:
	const unsigned int m_InitValue = 2;
	std::atomic<unsigned int> m_Initialized{ 0 };

	std::map<unsigned int, Channel_t> m_Channels; //PAWN channel-id to actual channel map

private:
	void AddChannel(json &data);

public:
	void Initialize(AMX *amx);
	void WaitForInitialization();

	Channel_t const &FindChannel(ChannelId_t id);
	Channel_t const &FindChannelByName(std::string const &name);
	Channel_t const &FindChannelById(Snowflake_t const &sfid);
};