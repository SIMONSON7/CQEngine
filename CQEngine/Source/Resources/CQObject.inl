inline CQEngine::CQObject::~CQObject() 
{

}

inline void CQObject::setName(const std::string _name)
{
	name_ = _name;
}

inline const std::string& CQObject::getName() const
{
	return name_;
}

inline const uint32_t CQObject::getTag() const
{
	return tag_;
}

inline void CQObject::setTag(uint32_t _tag)
{
	tag_ = _tag;
}

inline const uint64_t CQObject::getID() const
{
	return id_;
}