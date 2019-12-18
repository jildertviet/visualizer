typedef struct{
	float2 vel;
    float2 spawnPos;
	float mass;
	float alpha;		// need this to make sure the float2 vel is aligned to a 16 byte boundary
//    float fadeInValue;
//    float dummy;
} particleSystemParticle;

__kernel void updateParticle(
                             __global particleSystemParticle* particles,
                             __global float2* posBuffer,
                             const float2 dimensions, // 2
                             read_only image2d_t vecField, // 3
                             __global float4* colors,
                             const float2 globalForce, // Move all particles w/ this force (wind, graviy like)
                             const float2 forceMultiplier,
                             const float traagheid,
                             const float fadeIncrease,
                             const float destAlpha
                             ){
    
    int id = get_global_id(0);
    __global particleSystemParticle *p = &particles[id];
    
    if(colors[id][3] < destAlpha){
        colors[id][3] = colors[id][3] + (fadeIncrease);
    }
    
    float2 positionOnTexture = posBuffer[id] / dimensions; // Dimensions of the particleSystem-space (1280*800)
    float xCoord = positionOnTexture.x; // 0 - 1
    float yCoord = positionOnTexture.y;
    xCoord = xCoord * get_image_width(vecField);
    yCoord = yCoord * get_image_height(vecField);
    
    sampler_t smp = CLK_FILTER_LINEAR | CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_NONE; // Config for the texture

    float2 coor = (float2)( xCoord, yCoord);
    float2 normCoor = convert_float2(coor) / (float2)( get_image_width(vecField), get_image_height(vecField) );
    float4 force = read_imagef(vecField, smp, normCoor); // 0 - 1
    
    if(force[3] != 0){
        force.x -= 0.5; // Convert force to - and + range
        force.y -= 0.5;
    
//        force.x = force.x;
//        force.y = force.y * forceMultiplier.y;
    }
    
    force.x = (force.x + globalForce.x) * forceMultiplier.x;
    force.y = (force.y + globalForce.y) * forceMultiplier.y;
    
    float m = p->mass;
    p->vel.x = (p->vel.x * traagheid) + (((p->vel.x * (1.0 - m)) + ((force.x * 10000.) * m)) * (1.0 - traagheid)); // *10000 because velocity is stored in 0-10000 value
    p->vel.y = (p->vel.y * traagheid) + (((p->vel.y * (1.0 - m)) + ((force.y * 10000.) * m)) * (1.0 - traagheid));
    
    
//    posBuffer[id].x += ((p->vel.x * (p->mass * 3)) * 1) + 0; // Wind to the right
//    posBuffer[id].y += ((p->vel.y * (p->mass * 3)) * 1);
    
    posBuffer[id].x += (p->vel.x / 10000.);
    posBuffer[id].y += (p->vel.y / 10000.);
    
    if(posBuffer[id].x >= dimensions.x || posBuffer[id].x <= 0){
        posBuffer[id] = p->spawnPos; colors[id][3] = 0;
    }
    if(posBuffer[id].y >= dimensions.y || posBuffer[id].y <= 0){
        posBuffer[id] = p->spawnPos; colors[id][3] = 0;
    }
}
