/*
\author      name : BeomGeun Choi
\par         the assignment Number : 8
\par         the course name : CS250
\par         the term : SP_Ring 2018

*/

#include "Interpolate.h"

 float TexturedCoord::color_scale;
 Texture * TexturedCoord::texture;
TexturedCoord MakeInterSection(const  TexturedCoord &A, const   TexturedCoord &B, const  HalfSpace& H)
{
    const float t = dot(H, A) / (dot(H, A) - dot(H, B));
    float u = (1 - t) * A.u + t * B.u;
    float v = (1 - t) * A.v + t * B.v;
    return TexturedCoord(Hcoord((1 - t) * A + t * B),u,v);
}
void FillTriangle(Raster & r, const TexturedCoord & P , const TexturedCoord & Q, const TexturedCoord & R)
{    
    float inverseSlope[3]{ 0.f,0.f,0.f };

    TexturedCoord _p = TexturedCoord(1 / P.w * P,P.u,P.v);
    TexturedCoord _q = TexturedCoord(1 / Q.w * Q, Q.u, Q.v);
    TexturedCoord _r = TexturedCoord(1 / R.w * R, R.u, R.v);
    TexturedCoord topVec = _p;
    TexturedCoord middleVec = _q;
    TexturedCoord bottomVec = _r;
    auto P_Q = _q - _p;
    auto P_R = _r - _p;
    auto dt = P_Q.x*P_R.y - P_Q.y*P_R.x;

    if (topVec.y < bottomVec.y)
    {
        TexturedCoord TCsave = topVec;
        topVec = bottomVec;
        bottomVec = TCsave;
    }
    if (topVec.y < middleVec.y)
    {
        TexturedCoord TCsave = topVec;
        topVec = middleVec;
        middleVec = TCsave;
    }
    else if (middleVec.y < bottomVec.y)
    {
        TexturedCoord TCsave = middleVec;
        middleVec = bottomVec;
        bottomVec = TCsave;
    }

    inverseSlope[0] = (middleVec.x - bottomVec.x) / (middleVec.y - bottomVec.y);
    inverseSlope[1] = (topVec.x - bottomVec.x) / (topVec.y - bottomVec.y);
    inverseSlope[2] = (topVec.x - middleVec.x) / (topVec.y - middleVec.y);



    auto nor = cross(middleVec - topVec, bottomVec - topVec);

    auto U = cross(Vector
    (middleVec.x - topVec.x, middleVec.y - topVec.y, middleVec.u - topVec.u),
        Vector(bottomVec.x - topVec.x, bottomVec.y - topVec.y, bottomVec.u - topVec.u));

    auto V = cross(Vector(middleVec.x - topVec.x, middleVec.y - topVec.y, middleVec.v - topVec.v),
        Vector(bottomVec.x - topVec.x, bottomVec.y - topVec.y, bottomVec.v - topVec.v));


    const Hcoord interpolationz = Hcoord(nor.x, nor.y, nor.z, 
        topVec.x * nor.x + topVec.y * nor.y + topVec.z * nor.z);
    const Hcoord interpolatioNu = Hcoord(U.x, U.y, U.z,
        topVec.x * U.x + topVec.y * U.y + topVec.u * U.z);
    const Hcoord interpolationv = Hcoord(V.x, V.y, V.z,  
        topVec.x * V.x + topVec.y * V.y + topVec.v * V.z);

    if (inverseSlope[0] > inverseSlope[1])
    {
       

        int j_min = static_cast<int>(ceil(bottomVec.y));
        int j_max = static_cast<int>(floor(middleVec.y));

        for (int j = j_min; j <= j_max; ++j)
        {
            int x_min = static_cast<int>(bottomVec.x + inverseSlope[1] * (j - bottomVec.y));
            int x_max = static_cast<int>(bottomVec.x + inverseSlope[0] * (j - bottomVec.y));
            int i_min = static_cast<int>(ceil(x_min));
            int i_max = static_cast<int>(floor(x_max));
            r.GotoPoint(i_min, j);

            for (int i = i_min; i < i_max; ++i)
            {
                float Lambda, Mu, Nu;
                auto minus_p = -_p;
                minus_p.x += i;
                minus_p.y += j;

    

                Mu = (minus_p.x*P_R.y - minus_p.y*P_R.x) / dt;
                Nu = (minus_p.y*P_Q.x - minus_p.x*P_Q.y) / dt;
                Lambda = 1 - Mu - Nu;

                float z = (interpolationz.w - interpolationz.x*i - interpolationz.y*j) / interpolationz.z;
                float u = (interpolatioNu.w - interpolatioNu.x*i - interpolatioNu.y*j) / interpolatioNu.z;
                float v = (interpolationv.w - interpolationv.x*i - interpolationv.y*j) / interpolationv.z;
                

                if (z < r.GetZ())
                {
                    float Lambdadev = Lambda / P.w;
                    float Mudev = Mu / Q.w;
                    float Nudev = Nu / R.w;
                    float div = Lambdadev + Mudev + Nudev;

                    Lambda = Lambdadev / div;
                    Mu = Mudev / div;
                    Nu = Nudev / div;



                    u = Lambda * P.u + Mu * Q.u + Nu * R.u;
                    v = Lambda * P.v + Mu * Q.v + Nu * R.v;
                    Vector color = TexturedCoord::color_scale * TexturedCoord::texture->uvToRGB(u, v) ;
                    r.SetColor(static_cast<Raster::byte>(color.x), 
                        static_cast<Raster::byte>(color.y), 
                        static_cast<Raster::byte>(color.z));
                    r.WritePixel();
                    r.WriteZ(z);
                }
                r.IncrementX();
            }
        }
        j_min = static_cast<int>(ceil(middleVec.y));
        j_max = static_cast<int>(floor(topVec.y));

        for (int j = j_min; j <= j_max; ++j)
        {

            int x_min = static_cast<int>(topVec.x - inverseSlope[1] * (topVec.y - j));
            int x_max = static_cast<int>(middleVec.x + inverseSlope[2] * (j - middleVec.y));
            int i_min = static_cast<int>(ceil(x_min));
            int i_max = static_cast<int>(floor(x_max));
            r.GotoPoint(i_min, j);

            for (int i = i_min; i < i_max; ++i)
            {

                float Lambda, Mu, Nu;
                auto minus_p = -_p;
                minus_p.x += i;
                minus_p.y += j;

                Mu = (minus_p.x*P_R.y - minus_p.y*P_R.x) / dt;
                Nu = (minus_p.y*P_Q.x - minus_p.x*P_Q.y) / dt;
                Lambda = 1 - Mu - Nu;
          

                auto z = (interpolationz.w - interpolationz.x*i - interpolationz.y*j) / interpolationz.z;
                auto u = (interpolatioNu.w - interpolatioNu.x*i - interpolatioNu.y*j) / interpolatioNu.z;
                auto v = (interpolationv.w - interpolationv.x*i - interpolationv.y*j) / interpolationv.z;

                if (z < r.GetZ())
                {

                    auto Lambda_ = Lambda / P.w;
                    auto Mudev = Mu / Q.w;
                    auto Nudev = Nu / R.w;
                    auto div = Lambda_ + Mudev + Nudev;

                    Lambda = Lambda_ / div;
                    Mu = Mudev / div;
                    Nu = Nudev / div;

                    u = Lambda * P.u + Mu * Q.u + Nu * R.u;
                    v = Lambda * P.v + Mu * Q.v + Nu * R.v;
                    Vector color = TexturedCoord::color_scale *TexturedCoord::texture->uvToRGB(u, v);
                    r.SetColor(static_cast<Raster::byte>(color.x),
                        static_cast<Raster::byte>(color.y),
                        static_cast<Raster::byte>(color.z));
                    r.WritePixel();
                    r.WriteZ(z);
                }
                r.IncrementX();
            }
        }
    }
    else
    {
        int j_min = static_cast<int>(ceil(bottomVec.y));
        int j_max = static_cast<int>(floor(middleVec.y));


        for (int j = j_min; j <= j_max; ++j)
        {
            int x_min = static_cast<int>(bottomVec.x + inverseSlope[0] * (j - bottomVec.y));
            int x_max = static_cast<int>(bottomVec.x + inverseSlope[1] * (j - bottomVec.y));
            int i_min = static_cast<int>(ceil(x_min));
            int i_max = static_cast<int>(floor(x_max));
            r.GotoPoint(i_min, j);

            for (int i = i_min; i < i_max; ++i)
            {


                float Lambda, Mu, Nu;
                auto minus_p = -_p;
                minus_p.x += i;
                minus_p.y += j;


                Mu = (minus_p.x*P_R.y - minus_p.y*P_R.x) / dt;
                Nu = (minus_p.y*P_Q.x - minus_p.x*P_Q.y) / dt;
                Lambda = 1 - Mu - Nu;

                auto z = (interpolationz.w - interpolationz.x*i - interpolationz.y*j) / interpolationz.z;
                auto u = (interpolatioNu.w - interpolatioNu.x*i - interpolatioNu.y*j) / interpolatioNu.z;
                auto v = (interpolationv.w - interpolationv.x*i - interpolationv.y*j) / interpolationv.z;
                if (z < r.GetZ())
                {
                    auto Lambda_ = Lambda / P.w;
                    auto Mudev = Mu / Q.w;
                    auto Nudev = Nu / R.w;
                    auto div = Lambda_ + Mudev + Nudev;

                    Lambda = Lambda_ / div;
                    Mu = Mudev / div;
                    Nu = Nudev / div;


                     u = Lambda * P.u + Mu * Q.u + Nu * R.u;
                     v = Lambda * P.v + Mu * Q.v + Nu * R.v;
                    Vector color = TexturedCoord::color_scale *TexturedCoord::texture->uvToRGB(u, v);
                    r.SetColor(static_cast<Raster::byte>(color.x),
                        static_cast<Raster::byte>(color.y),
                        static_cast<Raster::byte>(color.z));
                    r.WritePixel();
                    r.WriteZ(z);
                }
                r.IncrementX();
            }
        }
        j_min = static_cast<int>(ceil(middleVec.y));
        j_max = static_cast<int>(floor(topVec.y));

        for (int j = j_min; j <= j_max; ++j)
        {
            int x_min = static_cast<int>(middleVec.x + inverseSlope[2] * (j - middleVec.y));
            int x_max = static_cast<int>(topVec.x - inverseSlope[1] * (topVec.y - j));
            int i_min = static_cast<int>(ceil(x_min));
            int i_max = static_cast<int>(floor(x_max));
            r.GotoPoint(i_min, j);

            for (int i = i_min; i < i_max; ++i)
            {

                float Lambda, Mu, Nu;
                auto minus_p = -_p;
                minus_p.x += i;
                minus_p.y += j;
                Mu = (minus_p.x*P_R.y - minus_p.y*P_R.x) / dt;
                Nu = (minus_p.y*P_Q.x - minus_p.x*P_Q.y) / dt;
                Lambda = 1 - Mu - Nu;

                auto z = (interpolationz.w - interpolationz.x*i - interpolationz.y*j) / interpolationz.z;
                auto u = (interpolatioNu.w - interpolatioNu.x*i - interpolatioNu.y*j) / interpolatioNu.z;
                auto v = (interpolationv.w - interpolationv.x*i - interpolationv.y*j) / interpolationv.z;
                if (z < r.GetZ())
                {
                    auto Lambda_ = Lambda / P.w;
                    auto Mudev = Mu / Q.w;
                    auto Nudev = Nu / R.w;
                    auto div = Lambda_ + Mudev + Nudev;

                    Lambda = Lambda_ / div;
                    Mu = Mudev / div;
                    Nu = Nudev / div;
                    u = Lambda * P.u + Mu * Q.u + Nu * R.u;
                    v = Lambda * P.v + Mu * Q.v + Nu * R.v;
                    Vector color = TexturedCoord::color_scale *TexturedCoord::texture->uvToRGB(u, v);
                    r.SetColor(static_cast<Raster::byte>(color.x),
                        static_cast<Raster::byte>(color.y),
                        static_cast<Raster::byte>(color.z));
                    r.WritePixel();
                    r.WriteZ(z);
                }
                      r.IncrementX();
            }
        }

    }
}
void VertexChange(std::vector<TexturedCoord>& vertices, HalfSpace H, unsigned & IntersectionCheck)
{

    std::vector<TexturedCoord> SaveVector;
    size_t size = vertices.size() - 1;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        TexturedCoord Cur = vertices[i];
        TexturedCoord Next = vertices[(i + 1) % vertices.size()];

        if (i == size)
        {
            Cur = vertices[size];
            Next = vertices[0];

        }

        if (((dot(H, Cur) > 0) && (dot(H, Next) <= 0)))
            SaveVector.push_back(MakeInterSection(Cur, Next, H));
        if (((dot(H, Cur) <= 0) && (dot(H, Next) <= 0))) {
            SaveVector.push_back(Cur);
            IntersectionCheck++;
        }
        else if (((dot(H, Cur) <= 0) && (dot(H, Next) > 0))) {
            SaveVector.push_back(Cur);
            SaveVector.push_back(MakeInterSection(Cur, Next, H));
        }


    }



    vertices = SaveVector;

}

bool TextureClip::operator()(std::vector<TexturedCoord>& vertices)
{
    temp_vertices.clear();
    unsigned IntersectionChecking = 0;
    for (auto aH : half_spaces)
    {
        VertexChange(vertices, aH, IntersectionChecking);


    }

    if (IntersectionChecking == vertices.size())
        return false;
    return true;
}
