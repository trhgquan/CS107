#include "RDET.h"
#include "SectorReader.h"

//Getter
int RDET::size() { return _size; }
FAT* RDET::fat() { return _fat; };
BYTE* RDET::data() { return _data; };
std::vector<Entry> RDET::entries() { return _entries; };

//API
std::string RDET::toString() {return _toString();}


std::string RDET::_toString(int level) { return ""; }

void RDET::_getAllEntries() {
	int entry = _size / AbstractEntry::bytesPerEntry();
	std::vector<LongFilename> dummy;
	for (int i = 0; i < entry; ++i)
	{
		BYTE* buffer = _data + (AbstractEntry::bytesPerEntry() * i);
		if (0xE5 != buffer[0])
		{
			while (0x0F == buffer[0xB]) {
				LongFilename lfn(buffer);
				dummy.push_back(lfn);
				++i;
				buffer = _data + (AbstractEntry::bytesPerEntry() * i);
			}

			_entries.push_back(Entry(buffer, _fat, dummy));
			dummy.clear();
		}
	}
}

//Parse data from fat sector to RDET
void RDET::_readData() {

	//Get the [start; end] sector of RDET
	std::pair<int, int> sectors = _fat->trace(_fat->bootSector().BPB()->RDET_clusterNumber());

	//Number of bytes to read
	_size = (sectors.second - sectors.first + 1) *_fat->bootSector().BPB()->bytesPerSector();

	//Read all bytes from [start; end] sector of RDET
	SectorReader reader(_fat->drive(), sectors.first, _size);

	//_data = reader.sector();
	memcpy(_data, reader.sector(), _size * sizeof(BYTE));
	
	//get entries
	_getAllEntries();
}

RDET::RDET()
{
	//do nothing
}

RDET::RDET(FAT* fat) 
{
	_fat = fat;
	_readData();
}

RDET::~RDET()
{
	//do nothing
}
