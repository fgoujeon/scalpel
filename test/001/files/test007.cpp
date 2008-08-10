class Something::Kennel;

class Dog: public Animal, virtual private Walking::Quadruped
{
	public:	
		Dog(const Race& race, const Something::Kennel& kennel): race(race) {};
		bool operator==(const Dog& dog) const;
		using Walking::Quadruped::get_feet_count;

	private:
		Race race;
		const Something::Kennel& kennel;
};

