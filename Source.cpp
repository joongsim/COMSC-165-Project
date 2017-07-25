#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedList.h"

using namespace std;

struct Location
{
	double longitude;		
	double latitude;		
	string time;			// "YYYY:MM:DD HH:MM:SS"
	string fname;			// Full path
	Location *next;			// To point to next node
};

string formatPlacemark(Location*);

int main()
{
	// Test Location structure
	Location* test1 = new Location;
	test1->latitude = 33.3421;
	test1->longitude = 34.134;
	test1->time = "2017:07:22 12:22:33";
	test1->fname = "C:/Users/joonj/Documents/COMSC 165/Project/Project/Test.jpg";
	
	Location* test2 = new Location;
	test2->latitude = 35.34;
	test2->longitude = 36.3;
	test2->time = "2017:02:11 12:34:33";
	test2->fname = "C:/Users/joonj/Downloads/dXmULbx.jpg";

	test1->next = test2;
	test2->next = nullptr;

	// ofstream object for writing kml file
	ofstream handle;

	// Throw an exception on failure to open the file or on a write error.
	handle.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	// Open the KML file for writing:
	handle.open("ProjectSample.kml");

	// Write to the KML file:
	handle << "<?xml version='1.0' encoding='utf-8'?>\n";
	handle << "<kml xmlns='http://www.opengis.net/kml/2.2'>\n";

	handle << formatPlacemark(test1);

	handle << "</kml>\n";
	handle.close();
	
	return 0;
}

string formatPlacemark(Location *point)
{
	ostringstream ss;
	ss << "<Document>\n"
		<< "<name>Test.kml</name>\n"
		<< "<StyleMap id=\"m_ylw-pushpin\">\n"
		<< "<Pair>\n"
		<< "<key>normal</key>\n"
		<< "<styleUrl>#s_ylw-pushpin</styleUrl>\n"
		<< "</Pair>\n"
		<< "<Pair>\n"
		<< "<key>highlight</key>\n"
		<< "<styleUrl>#s_ylw-pushpin_hl0</styleUrl>\n"
		<< "</Pair>\n"
		<< "</StyleMap>\n"
		<< "<Style id =\"s_ylw-pushpin\">\n"
		<< "<IconStyle>\n"
		<< "<scale>1.1</scale>\n"
		<< "<Icon>\n"
		<< "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>\n"
		<< "</Icon>\n"
		<< "<hotSpot x = \"20\" y = \"2\" xunits = \"pixels\" yunits = \"pixels\"/>\n"
		<< "</IconStyle>\n"
		<< "<ListStyle>\n"
		<< "</ListStyle>\n"
		<< "</Style>\n"
		<< "<Style id=\"s_ylw-pushpin_hl\">\n"
		<< "<IconStyle>\n"
		<< "<scale>1.3</scale>\n"
		<< "<Icon>\n"
		<< "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>\n"
		<< "</Icon>\n"
		<< "<hotSpot x = \"20\" y = \"2\" xunits = \"pixels\" yunits = \"pixels\"/>\n"
		<< "</IconStyle>\n"
		<< "</Style>\n"
		<< "<Style id=\"s_ylw-pushpin0\">\n"
		<< "<IconStyle>\n"
		<< "<scale>1.1</scale>\n"
		<< "<Icon>\n"
		<< "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>\n"
		<< "</Icon>\n"
		<< "<hotSpot x=\"20\" y =\"2\" xunits=\"pixels\" yunits=\"pixels\"/>\n"
		<< "</IconStyle>\n"
		<< "</Style>"
		<< "<Style id=\"s_ylw-pushpin_hl0\">\n"
		<< "<IconStyle>\n"
		<< "<scale>1.3</scale>\n"
		<< "<Icon>\n"
		<< "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>\n"
		<< "</Icon>\n"
		<< "<hotSpot x=\"20\" y=\"2\" xunits=\"pixels\" yunits=\"pixels\"/>\n"
		<< "</IconStyle>\n"
		<< "<ListStyle>\n"
		<< "</ListStyle>\n"
		<< "</Style>\n"
		<< "<StyleMap id=\"m_ylw-pushpin0\">\n"
		<< "<Pair>\n"
		<< "<key>normal</key>\n"
		<< "<styleUrl>#s_ylw-pushpin0</styleUrl>\n"
		<< "</Pair>\n"
		<< "<Pair>\n"
		<< "<key>highlight</key>\n"
		<< "<styleUrl>#s_ylw-pushpin_hl</styleUrl>\n"
		<< "</Pair>\n"
		<< "</StyleMap>\n"
		<< "<Folder>\n"
		<< "<name>Test</name>\n"
		<< "<open>1</open>\n"
		<< "<Placemark>\n"
		<< "<name>Path</name>\n"
		<< "<styleUrl>#m_ylw-pushpin0</styleUrl>\n"
		<< "<LineString>\n"
		<< "<tessellate>1</tessellate>\n"
		<< "<coordinates>\n"
		// Need loop here to go through list
		<< point->latitude << "," << point->longitude << ",0\n"	// Writes list of coordinates
		<< "</coordinates>\n"
<< "</LineString>\n"
<< "</Placemark>\n"
<< "<Folder>\n"
<< "<name>Pictures</name>\n"
<< "<open>1</open>\n"

// Begin loop to traverse list
<< "<Placemark>\n"
<< "<name>Place 1</name>\n"	// replace with 
<< "<description><![CDATA[<img style = \"max-width:500px;\" src=\""
<< point->fname			// Writes image file path
<< "\">]]></description>\n"
<< "<styleUrl>#m_ylw-pushpin</styleUrl>\n"
<< "<Point>\n"
<< "<altitudeMode>relativeToGround</altitudeMode>\n"
<< "<gx:drawOrder>1</gx:drawOrder>\n"
<< "<coordinates>\n"
<< point->latitude << "," << point->longitude << ",0\n"		// Writes coordinates of placemark
<< "</coordinates>\n"
<< "</Point>\n"
<< "</Placemark>\n"
// End loop
<< "</Folder>\n"
<< "</Folder>\n"
<< "</Document>\n";

		
		
		
		/*ss << "<Placemark>\n"			// First writes path
		<< "<name>Path</name>\n"
		<< "<description>This is the path between the 2 points</description>\n"
		<< "<styleUrl>#pathstyle</styleUrl>\n"
		<< "<LineString>\n"
		<< "<tessellate>1</tessellate>\n"
		<< "<coordinates>"
		<< point.latitude << "," << point.longitude << ",0"
		<< " "
		<< 1.324 << "," << 3.2234 << ",0"
		<< "</coordinates>\n"
		<< "</LineString>\n"
		// Writing Points
		<< "<name>Placemark</name>\n"
		<< "<description>";
		<< "<![CDATA[<img src = "
		<< point.fname[i]
		<< ">]]></description>"
		<< "<Point>\n"
		<< "<coordinates>"
		<< point.latitude << "," << point.longitude << ",0"
		<< "</coordinates>"
		<< "</Point>"
		<< "</Placemark>";
		*/

	

	return ss.str();
}
