class Phone
{
	public:
		Phone(const BrandName& brand_name, const Color& color);
		const BrandName& get_brand_name() const;
		const Color& get_color() const;

	private:
		BrandName brand_name;
		Color color;
};

Phone::Phone(const BrandName& brand_name, const Color& color):
	brand_name(brand_name),
	color(color)
{
}

const BrandName& 
Phone::get_brand_name() const
{
	return brand_name;
}

const Color& 
Phone::get_color() const
{
	return color;
}

int main(int argc, char** argv)
{
	BrandName bn("PhoneTech");
	Phone* phone = new Phone(bn, Color::BLACK);

	std::cout << "My phone's brand name is " << phone->get_brand_name() << "\n";

	delete phone;

	return 0;
}
