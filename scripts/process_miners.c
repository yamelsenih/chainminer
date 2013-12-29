#include <stdio.h>
#include <string.h>

#define sizeofvector(a) (sizeof((a))/sizeof((a)[0]))


char *link(char*filename)
{
   static char buf[250];
   int l = strlen(filename);
   while(l > 0 && filename[l] != '.') l--;
   strncpy(buf, filename, l);
   sprintf(buf+l, ".stat.txt");
   
   return buf;
}

char *ip(char*filename)
{
   static char buf1[250];
   int l = strlen(filename);
   while(l > 0 && filename[l] != '.') l--;
   strncpy(buf1, filename, l);
   buf1[l] = 0;
   return buf1;
}


int main(int argc, char **argv)
{
  FILE *fp;
  int int_data[256][13];
  float float_data[256][4];
  int cnt;

  memset(int_data, 0, sizeof(int_data));
  memset(float_data, 0, sizeof(float_data));

  int_data[0][12] = 0;
  cnt = 1;
  for (int i = 1; i < argc; i++)
  {
//      printf("arg[%i] = %s\n", i, argv[i]);
      fp=fopen(argv[i],"r");
      if (fp == NULL)
              continue;
      int r;
      r = fscanf(fp,
                "%d,"      // total chips
                "%d,"       // speed
                "%f,"     // noncerate
                "%f,"     // speed per chip
                "%f,"     // hashrate
                "%d,"       // total chips
                "%d,"       // ok
                "%d,"       // slow
                "%d,"       // very slow
                "%d,"       // bad
                "%d,"       // good
                "%d,"       // errors
                "%d,"       // spi-errors
                "%d,"       // miso-errors
                "%d,"       // jobs
                "%f"     // record
                "\n",
                &int_data  [cnt][0],
                &int_data  [cnt][1],
                &float_data[cnt][0],
                &float_data[cnt][1],
                &float_data[cnt][2],
                &int_data  [cnt][2],
                &int_data  [cnt][3],
                &int_data  [cnt][4],
                &int_data  [cnt][5],
                &int_data  [cnt][6],
                &int_data  [cnt][7],
                &int_data  [cnt][8],
                &int_data  [cnt][9],
                &int_data  [cnt][10],
                &int_data  [cnt][11],
                &float_data[cnt][3]);
      int_data[cnt][12] = i;
      if (r == 16)
      	  cnt++;
      	
      fclose(fp);
   }

   if (cnt == 1)
   {
   	  printf("no valid files\n");
   	  return 0;
   }
   printf("cnt = %i\n", cnt);
   
   for (int i = 1; i < cnt; i++)
   {
      for (int j = 0; j<12; j++)
         int_data[0][j]+=int_data[i][j];
      for (int j = 0; j<4; j++)
         float_data[0][j]+=float_data[i][j];
   }
      
   	
   fp=fopen("index.html","w");
   if (fp != NULL)
   {
       fprintf(fp,"<html\">\n"
                  "<head>\n"
                  "    <link rel=\"stylesheet\" href=\"theme/style.css\" type=\"text/css\" id=\"\" media=\"print, projection, screen\" />\n"
                  "    <script type=\"text/javascript\" src=\"jq/jquery-latest.js\"></script>\n"
                  "    <script type=\"text/javascript\" src=\"jq/jquery.tablesorter.js\"></script> \n"
                  "    <script type=\"text/javascript\" id=\"js\">$(document).ready(function() {\n"
                  "    $(\"table\").tablesorter({\n"
		  "    sortList: [[0,0]]\n"
                  "	});\n}); </script>\n"
                  "</head>\n"
                  "<body>\n"
//                  "<table border=1 cellpadding=1 cellspacing=1 id=\"myTable\" class=\"tablesorter\">\n"
                  "<table id=\"myTable\" class=\"tablesorter\">\n"
                  "<thead>\n"
                  "<tr>\n"
                  "    <th>ip</th>\n"
     	   	  "    <th>total boards</th>\n"
   	   	  "    <th>speed</th>\n"
   	   	  "    <th>noncerate</th>\n"
   	   	  "    <th>speed per chip</th>\n"
   	   	  "    <th>hashrate</th>\n"
   	   	  "    <th>total chips</th>\n"
   	   	  "    <th>ok</th>\n"
   	   	  "    <th>slow</th>\n"
   	   	  "    <th>very slow</th>\n"
   	   	  "    <th>bad</th>\n"
   	   	  "    <th>good</th>\n"
   	   	  "    <th>errors</th>\n"
   	   	  "    <th>spi-errors</th>\n"
   	   	  "    <th>miso-errors</th>\n"
   	   	  "    <th>jobs</th>\n"
   	   	  "    <th>record</th>\n"
   	   	  "</tr>\n");
       for (int i = 0; i < cnt; i++)
       {
          fprintf(fp,"<tr>\n"
   	          "    <td><a href=\"%s\">%s</a></td>\n"      // ip
                  "    <td>%d</td>\n"      // total boards
                  "    <td>%d</td>\n"      // speed
                  "    <td>%f</td>\n"      // noncerate
                  "    <td>%f</td>\n"      // speed per chip
                  "    <td>%f</td>\n"      // hashrate
                  "    <td>%d</td>\n"       // total chips
                  "    <td>%d</td>\n"       // ok
                  "    <td>%d</td>\n"       // slow
                  "    <td>%d</td>\n"       // very slow
                  "    <td>%d</td>\n"       // bad
                  "    <td>%d</td>\n"       // good
                  "    <td>%d</td>\n"       // errors
                  "    <td>%d</td>\n"       // spi-errors
                  "    <td>%d</td>\n"       // miso-errors
                  "    <td>%d</td>\n"       // jobs
                  "    <td>%f</td>\n"     // record
                  "</tr>\n\n",
                  (i==0)?"index.txt":link(argv[int_data[i][12]]), (i==0)?"total":ip(argv[int_data[i][12]]),            
	                int_data  [i][0],
	                int_data  [i][1],
	                float_data[i][0],
                  (i==0) ? float_data[i][1] / (cnt-1) :  float_data[i][1],
	                float_data[i][2],
	                int_data  [i][2],
	                int_data  [i][3],
	                int_data  [i][4],
	                int_data  [i][5],
	                int_data  [i][6],
	                int_data  [i][7],
	                int_data  [i][8],
	                int_data  [i][9],
	                int_data  [i][10],
	                int_data  [i][11],
	                float_data[i][3]);

          if (i == 0)
             fprintf(fp,"</thead>\n<tbody>\n");

        }
   	    fprintf(fp,"</tbody>\n"
                       "</table>\n"
                       "</body>\n"
                       "</html>\n");
   }
   fclose(fp);


   fp=fopen("index.txt","w");
   if (fp != NULL)
   {
   	   fprintf(fp,  "ip,"
   	   							"total boards,"
   	   							"speed,"
   	   							"noncerate,"
   	   							"speed per chip,"
   	   							"hashrate,"
   	   							"total chips,"
   	   							"k,"
   	   							"slow,"
   	   							"very slow,"
   	   							"bad,"
   	   							"good,"
   	   							"errors,"
   	   							"spi-errors,"
   	   							"miso-errors,"
   	   							"jobs,"
   	   							"record\n");
   	   for (int i = 0; i < cnt; i++)
   	   		fprintf(fp,
   	   		        "%s,"      // ip
                  "%d,"      // total boards
                  "%d,"      // speed
                  "%f,"      // noncerate
                  "%f,"      // speed per chip
                  "%f,"      // hashrate
                  "%d,"       // total chips
                  "%d,"       // ok
                  "%d,"       // slow
                  "%d,"       // very slow
                  "%d,"       // bad
                  "%d,"       // good
                  "%d,"       // errors
                  "%d,"       // spi-errors
                  "%d,"       // miso-errors
                  "%d,"       // jobs
                  "%f\n",     // record
                  (i==0)?"total":argv[int_data[i][12]],            
	                int_data  [i][0],
	                int_data  [i][1],
	                float_data[i][0],
                 (i==0) ? float_data[i][0] / int_data  [i][2] :  float_data[i][1],
	                float_data[i][2],
	                int_data  [i][2],
	                int_data  [i][3],
	                int_data  [i][4],
	                int_data  [i][5],
	                int_data  [i][6],
	                int_data  [i][7],
	                int_data  [i][8],
	                int_data  [i][9],
	                int_data  [i][10],
	                int_data  [i][11],
	                float_data[i][3]);
   	    fprintf(fp,"\n");
   }
   fclose(fp);

   
   return 0;
}


