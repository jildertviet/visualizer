#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect prevPosData;  // recive the previus position texture
uniform sampler2DRect velData;      // recive the velocity texture

uniform float timestep;

//vec2 resetPos(vec2 spawnPos){
//    vec2 o;
//    o.y = decode(spawnPos);
//    o.x = 0.005 * MAXVAL;
//    //    vec2 o = (spawnPos * MAXVAL * 0.95) + (MAXVAL * 0.05);
//    //    o.x = 0.1 * MAXVAL;
//    return o;
//}

void main(void){
    vec2 st = gl_TexCoord[0].st;    // gets the position of the pixel that it´s dealing with...
    
    vec2 pos = texture2DRect( prevPosData, st ).xy; // ... in order to look at a particulary place on it
    float mass = texture2DRect( prevPosData, st ).z;
    vec2 vel = texture2DRect( velData, st ).xy;     // Fetch both the pos and vel.
    
    pos += vel * timestep; // Updates the position
    
    pos += vec2(0.001, 0); // WIND!?
    
    if(pos.x >= 1.0){
        pos.x = 0.;
    }
    if(pos.y <= 0.)
        pos.x = 0.;
    if(pos.y >= 1.0)
        pos.x = 0;
    
//    } else if(p.x <= 0.04){
//
//    }
//    if(pos.y >= 1.0){
//        pos = resetPos(spawnPos);
//    } else if(pos.y <= 0.01){
//        pos = resetPos(spawnPos);
//    }
    
    
    gl_FragColor.rgba = vec4(pos.x,pos.y,mass,1.0);  // And finaly it store it on the position FBO
}
