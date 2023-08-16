#include "stdafx.h"
#include "colors.h"

namespace Colors
{
    void computeColorTables()
    {
        hue = COLORHUE % 360;
        g_hueshift = HUEMEAN;

        // allocate
        for (int i = 0; i < 36000; i++)
            varhue_table[i] = HSLToRGB((double)i / 100.0, 0.8, 0.5);
        for (int i = 0; i < 10000; i++)
            varlume_table[i] = HSLToRGB(hue, 0.7, (double)i / 100.0);

        for (int i = 0; i < 200000; i++)
            tanh_table[i] = tanh((double)(i - 100000) / 1000.0);
    }

    static void freeColorTables()
    {
        y = 0.5;
        varhue_table.clear();
        varlume_table.clear();
        tanh_table.clear();
    }

    sf::Color color_scheme(double& value, double& scale)
    {
        //variable lume

        //y = LUMMEAN + tanh(SLOPE * value / scale) * LUMAMP;
        //intpart = (int)y;
        //y -= (double)intpart;
        //rgb = varlume_table.at((int)(y*100.0));


        //variable hue

        amplitude = tanh_table[(int)((SLOPE * value / scale) * 1000) + 100000];

        hue = g_hueshift + amplitude * HUEAMP;
        if (hue < 0) hue += 360;
        if (hue >= 360) hue -= 360;
        rgb = varhue_table[((int)(hue * 100))];
        //rgb = HSLToRGB(hue, 0.8, 0.5);

        return rgb;
    }


    /* color conversion from HSL to RGB */
    static sf::Color HSLToRGB(double h, double s, double l) {
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;

        if (s == 0)
        {
            r = g = b = (unsigned char)(l * 255);
        }
        else
        {
            double v1, v2;
            double hue = (double)h / 360.0;

            v2 = (l < 0.5) ? (l * (1 + s)) : ((l + s) - (l * s));
            v1 = 2 * l - v2;

            r = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0 / 3)));
            g = (unsigned char)(255 * HueToRGB(v1, v2, hue));
            b = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0 / 3)));
        }

        return sf::Color(r, g, b, 255);
    }

    static float HueToRGB(double v1, double v2, double vH) {
        if (vH < 0)
            vH += 1;

        if (vH > 1)
            vH -= 1;

        if ((6 * vH) < 1)
            return (v1 + (v2 - v1) * 6 * vH);

        if ((2 * vH) < 1)
            return v2;

        if ((3 * vH) < 2)
            return (v1 + (v2 - v1) * ((2.0 / 3) - vH) * 6);

        return v1;
    }
    /* compute the variance of the field, to adjust color scheme */
    //double compute_variance(vector<vector<double>> u, vector<vector<double>> q)
    //{
    //    int i, j, n = 0;
    //    double variance = 0.0;
    //
    //    for (i = 1; i < Nx; i++)
    //        for (j = 1; j < Ny; j++)
    //        {
    //            if (q[i][j] > 0)
    //            {
    //                n++;
    //                variance += u[i][j] * u[i][j];
    //            }
    //        }
    //    if (n == 0) n = 1;
    //    return(variance / (double)n);
    //}

}