#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
class User
{
public:
	User() = delete;
	User(const std::string& username);
	~User() = default;
public:
	bool operator==(User&) const;
	std::string getName() const;
	void startFriendship(std::shared_ptr<User> user);
	void stopFriendship(std::shared_ptr<User> user);
	void bfsSearch() const;
private:
	std::string m_username;
	std::vector<std::shared_ptr<User>> m_friends;
	mutable int counter = 0;
};

template<typename T>
void remove(std::vector<T>& v, const T& item)
{
	v.erase(std::remove(v.begin(), v.end(), item), v.end());
}

int main()
{
	
	const std::vector<std::string> dataNames =
	{
	"Adams",	"Baker",	"Clark",	"Davis",
	"Evans",	"Frank",	"Ghosh",	"Hills",
	"Irwin",	"Jones",	"Klein",	"Lopez",
	"Mason",	"Nalty",	"Ochoa",	"Patel",
	"Quinn",	"Reily",	"Smith",	"Trott",
	"Usman",	"Valdo",	"White",	"Xiang",
	"Yakub",	"Zafar",
	};
	std::vector<std::shared_ptr<User>> dataUsers;
	for (const auto& element : dataNames)
	{
		dataUsers.emplace_back(std::make_shared<User>(element));
	}

	for (size_t i = 0; i < 5; ++i)
	{
		dataUsers[i]->startFriendship(dataUsers[i + 1]);
	}

	for (size_t i = 1; i < 6; ++i)
	{
		dataUsers[i]->startFriendship(dataUsers[i + 8]);
	}
	dataUsers[0]->bfsSearch();
}

User::User(const std::string& username)
	:m_username(username),m_friends()
{
}

bool User::operator==(User& rhs) const
{
	return this->m_username == rhs.m_username;
}

std::string User::getName() const
{
	return m_username;
}

void User::startFriendship(std::shared_ptr<User> user)
{
	if(std::find(m_friends.begin(),m_friends.end(),user) == m_friends.end())
		m_friends.emplace_back(std::move(user));
}

void User::stopFriendship(std::shared_ptr<User> user)
{
	remove(this->m_friends, user);
}

void User::bfsSearch() const
{
	std::vector<std::shared_ptr<User>> dataFriends;
	for (const auto& element : this->m_friends)
	{
		if (std::find(dataFriends.begin(), dataFriends.end(), element) == dataFriends.end())
			dataFriends.push_back(element);
	}

	std::cout << "First hand!\n";
	for (const auto& element : dataFriends)
	{
		std::cout << element->getName() << '\n';
	}
	for (const auto& element : this->m_friends)
	{

		for (const auto& element : element->m_friends)
		{
			if (std::find(dataFriends.begin(), dataFriends.end(), element) == dataFriends.end())
				dataFriends.push_back(element);
		}
	}

	std::cout << "Second hand!\n";
	for (const auto& element : dataFriends)
	{
		std::cout << element->getName() << '\n';
	}
	for (const auto& element : this->m_friends)
	{
		for (const auto& element : element->m_friends)
		{

			for (const auto& element : element->m_friends)
			{
				if (std::find(dataFriends.begin(), dataFriends.end(), element) == dataFriends.end())
					dataFriends.push_back(element);
			}
		}
	}
	std::cout << "Third hand!\n";
	for (const auto& element : dataFriends)
	{
		std::cout << element->getName() << '\n';
	}
	// depth 4
	/*
	for (const auto& element : this->m_friends)
	{
		for (const auto& element : element->m_friends)
		{
			for (const auto& element : element->m_friends)
			{

				for (const auto& element : element->m_friends)
				{
					if (std::find(dataFriends.begin(), dataFriends.end(), element) == dataFriends.end())
						dataFriends.push_back(element);
				}
			}
		}
	}
	std::cout << "Fourth hand!\n";
	for (const auto& element : dataFriends)
	{
		std::cout << element->getName() << '\n';
	}*/
}

